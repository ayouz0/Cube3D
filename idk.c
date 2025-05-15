
typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img_ptr;
	char		*addr;
	float		fov;
	t_player	player;
	t_keys		keys;
	t_parser	parse_data;
	t_ray		ray;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			light;
	t_door		*doors;
	int			door_count;
	t_cardinals	door_tex;
	t_cardinals	light_img[8];
	t_minimap	minimap;
}	t_game;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
	int	door_key;
}	t_keys;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	float	horz_hit_x;
	float	horz_hit_y;
	int		horz_hit_is_door;
	float	vert_hit_x;
	float	vert_hit_y;
	int		vert_hit_is_door;
	int		found_horz_hit;
	int		found_vert_hit;
	float	next_horz_x;
	float	next_horz_y;
	float	next_vert_x;
	float	next_vert_y;
}	t_ray;


typedef struct s_cardinals
{
	void	*ptr;
	int		h;
	int		w;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_cardinals;

int	iswall(float x, float y, char **map, int door_key)
{
	int	map_x;
	int	map_y;

	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key % 2 != 0))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y - PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key % 2 != 0))
		return (1);
	map_x = (int)((x - PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key % 2 != 0))
		return (1);
	map_x = (int)((x + PLAYER_RADIUS) / TILESIZE);
	map_y = (int)((y + PLAYER_RADIUS) / TILESIZE);
	if (map[map_y][map_x] == '1' || (map[map_y][map_x] == 'D' && door_key % 2 != 0))
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	t_game	game;
	(void)av;
	(void)ac;
	atexit(leaks);
	game.mlx = mlx_init();
	game.parse_data.no.ptr = NULL;
	game.parse_data.so.ptr = NULL;
	game.parse_data.we.ptr = NULL;
	game.parse_data.ea.ptr = NULL;
	game.parse_data.fd = -1;
	if (parsing(ac, av, &game) != 0)
		return (free_parse_data(&game), 1);
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3d");
	game.img_ptr = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img_ptr, &game.bits_per_pixel, &game.line_length, &game.endian);
	game.keys.a = 0;
	game.keys.d = 0;
	game.keys.s = 0;
	game.keys.w = 0;
	game.keys.door_key = 1;
	game.keys.left = 0;
	game.keys.right= 0;
	game.keys.esc = 0;
	init_doors(&game);
	init_player(&game.player, &game);
	init_minimap(&game);
	init_light(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_loop_hook(game.mlx, combined_update, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}


void	move_player(t_game *game, float angle)
{
	float	movestep;
	float	new_x;
	float	new_y;

	movestep = game->player.mv.mov_speed;
	new_x = game->player.player_x + cos(angle) * movestep;
	new_y = game->player.player_y + sin(angle) * movestep;
	if (!iswall(new_x, new_y, game->map, game->keys.door_key))
	{
		game->player.player_x = new_x;
		game->player.player_y = new_y;
	}
}

void update_doors(t_game *game)
{
	for (int i = 0; i < game->door_count; i++)
	{
		// If door is animating
		if (game->doors[i].animation_dir != 0)
		{
			// Update open_state based on direction
			game->doors[i].open_state += game->doors[i].animation_dir * 0.05;
			
			// Clamp values between 0 and 1
			if (game->doors[i].open_state >= 1.0)
			{
				game->doors[i].open_state = 1.0;
				game->doors[i].is_open = 1;
				game->doors[i].animation_dir = 0;
			}
			else if (game->doors[i].open_state <= 0.0)
			{
				game->doors[i].open_state = 0.0;
				game->doors[i].is_open = 0;
				game->doors[i].animation_dir = 0;
			}
		}
	}
}

void check_door_interaction(t_game *game)
{
    // Only process if door key was just pressed (not held)
    if (game->keys.door_key == 0)
        return;
        
    // Reset the door key after processing
    game->keys.door_key = 0;
    
    // Check if player is near a door
    int player_map_x = floor(game->player.player_x / TILESIZE);
    int player_map_y = floor(game->player.player_y / TILESIZE);
    
    // Check surrounding tiles for doors
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            int check_x = player_map_x + x;
            int check_y = player_map_y + y;
            
            // Skip if out of bounds
            if (check_x < 0 || check_y < 0 || 
                check_x >= game->parse_data.width || 
                check_y >= game->parse_data.height)
                continue;
                
            // If this is a door tile
            if (game->map[check_y][check_x] == 'D')
            {
                // Find door in array
                for (int i = 0; i < game->door_count; i++)
                {
                    if (game->doors[i].x == check_x && game->doors[i].y == check_y)
                    {
                        // Toggle door state
                        if (game->doors[i].is_open || game->doors[i].animation_dir > 0)
                            game->doors[i].animation_dir = -1;  // Close door
                        else
                            game->doors[i].animation_dir = 1;   // Open door
                            
                        // Only handle one door at a time
                        return;
                    }
                }
            }
        }
    }
}

int	update(t_game *game)
{
	if (game->keys.left)
		game->player.mv.player_angle -= game->player.mv.rotspeed;
	if (game->keys.right)
		game->player.mv.player_angle += game->player.mv.rotspeed;
	if (game->keys.w)
		move_player(game, game->player.mv.player_angle);
	if (game->keys.s)
		move_player(game, game->player.mv.player_angle + M_PI);
	if (game->keys.a)
		move_player(game, game->player.mv.player_angle - M_PI_2);
	if (game->keys.d)
		move_player(game, game->player.mv.player_angle + M_PI_2);
	game->player.mv.player_angle = norma_angle(game->player.mv.player_angle);
	check_door_interaction(game);
    update_doors(game);
	clear_image(game);
	draw_sky(game);
	draw_floor(game);
	cast_all_rays(game, &game->ray);
	if (game->light  % 2 == 0)
		animate_sprite(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
	return (0);
}




void	init_ray_hits(t_ray *ray)
{
	ray->found_horz_hit = 0;
	ray->found_vert_hit = 0;
	ray->horz_hit_x = 0;
	ray->horz_hit_y = 0;
	ray->vert_hit_x = 0;
	ray->vert_hit_y = 0;
}

void	choose_closest_hit(t_game *game, t_ray *ray)
{
	float	horz_dist;
	float	vert_dist;

	if (ray->found_horz_hit)
	{
		horz_dist = distance_between_points(game->player.player_x,
				game->player.player_y, ray->horz_hit_x, ray->horz_hit_y);
	}
	else
		horz_dist = INFINITY;
	if (ray->found_vert_hit)
	{
		vert_dist = distance_between_points(game->player.player_x,
				game->player.player_y, ray->vert_hit_x, ray->vert_hit_y);
	}
	else
		vert_dist = INFINITY;
	set_closest_hit(ray, horz_dist, vert_dist);
}

void	cast_single_ray(t_game *game, t_ray *ray)
{
	int	facing_up;
	int	facing_down;
	int	facing_left;
	int	facing_right;

	ray->ray_angle = norma_angle(ray->ray_angle);
	facing_down = (ray->ray_angle > 0 && ray->ray_angle < M_PI);
	facing_up = !facing_down;
	facing_right = (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI);
	facing_left = !facing_right;
	init_ray_hits(ray);
	check_horizontal_hit(game, ray, facing_up);
	check_vertical_hit(game, ray, facing_left);
	choose_closest_hit(game, ray);
}

void	render_wall_slice(t_game *game, t_ray *ray, int ray_id)
{
	int		wall_height;
	float	corrected_dist;
	float	proj_plane_dist;

	corrected_dist = ray->distance * \
		cos(ray->ray_angle - game->player.mv.player_angle);
	proj_plane_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	wall_height = (TILESIZE / corrected_dist) * proj_plane_dist;
	draw_textured_column(game, ray, ray_id, wall_height);
}

void	cast_all_rays(t_game *game, t_ray *ray)
{
	int		ray_id;
	float	ray_angle;

	ray_id = 0;
	ray_angle = game->player.mv.player_angle - (FOV / 2);
	while (ray_id < NUM_RAYS)
	{
		ray->ray_angle = ray_angle;
		cast_single_ray(game, ray);
		render_wall_slice(game, ray, ray_id);
		ray_angle += FOV / NUM_RAYS;
		ray_id++;
	}
}

void	prepare_horizontal_check(t_game *game, t_ray *ray,
				float *x_step, float *y_step)
{
	float	y_intercept;
	float	x_intercept;

	y_intercept = floor(game->player.player_y / TILESIZE) * TILESIZE;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		y_intercept += TILESIZE;
	x_intercept = game->player.player_x + \
			(y_intercept - game->player.player_y) / tan(ray->ray_angle);
	*y_step = TILESIZE;
	if (!(ray->ray_angle > 0 && ray->ray_angle < M_PI))
		*y_step *= -1;
	*x_step = TILESIZE / tan(ray->ray_angle);
	if ((ray->ray_angle > M_PI_2 && \
		ray->ray_angle < 3 * M_PI_2 && \
		*x_step > 0) || ((ray->ray_angle < M_PI_2 || \
		ray->ray_angle > 3 * M_PI_2) && *x_step < 0))
		*x_step *= -1;
	ray->next_horz_x = x_intercept;
	ray->next_horz_y = y_intercept;
}

void	check_horizontal_hit(t_game *game, t_ray *ray,
				int facing_up)
{
	float	x_step;
	float	y_step;
	int		check_y;
	int		hit_type;

	prepare_horizontal_check(game, ray, &x_step, &y_step);
	while (ray->next_horz_x >= 0 && \
		ray->next_horz_x <= game->parse_data.width * TILESIZE && \
		ray->next_horz_y >= 0 && \
		ray->next_horz_y <= game->parse_data.height * TILESIZE)
	{
		if (facing_up)
			check_y = ray->next_horz_y - 1;
		else
			check_y = ray->next_horz_y;
		hit_type = has_wall_at(ray->next_horz_x, check_y, game);
		if (hit_type > 0)
		{
			ray->found_horz_hit = 1;
			ray->horz_hit_x = ray->next_horz_x;
			ray->horz_hit_y = ray->next_horz_y;
			ray->horz_hit_is_door = (hit_type == 2);
			return ;
		}
		ray->next_horz_x += x_step;
		ray->next_horz_y += y_step;
	}
}

void	prepare_vertical_check(t_game *game, t_ray *ray,
				float *x_step, float *y_step)
{
	float	x_intercept;
	float	y_intercept;

	x_intercept = floor(game->player.player_x / TILESIZE) * TILESIZE;
	if (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
		x_intercept += TILESIZE;
	y_intercept = game->player.player_y + \
			(x_intercept - game->player.player_x) * tan(ray->ray_angle);
	*x_step = TILESIZE;
	if (!(ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI))
		*x_step *= -1;
	*y_step = TILESIZE * tan(ray->ray_angle);
	if ((ray->ray_angle > M_PI && *y_step > 0) || \
		(ray->ray_angle < M_PI && *y_step < 0))
		*y_step *= -1;
	ray->next_vert_x = x_intercept;
	ray->next_vert_y = y_intercept;
}

void	check_vertical_hit(t_game *game, t_ray *ray,
				int facing_left)
{
	float	x_step;
	float	y_step;
	int		check_x;
	int		hit_type;

	prepare_vertical_check(game, ray, &x_step, &y_step);
	while (ray->next_vert_x >= 0 && \
		ray->next_vert_x <= game->parse_data.width * TILESIZE && \
		ray->next_vert_y >= 0 && \
		ray->next_vert_y <= game->parse_data.height * TILESIZE)
	{
		if (facing_left)
			check_x = ray->next_vert_x - 1;
		else
			check_x = ray->next_vert_x;
		hit_type = has_wall_at(check_x, ray->next_vert_y, game);
		if (hit_type)
		{
			ray->found_vert_hit = 1;
			ray->vert_hit_x = ray->next_vert_x;
			ray->vert_hit_y = ray->next_vert_y;
			ray->vert_hit_is_door = (hit_type == 2);
			return ;
		}
		ray->next_vert_x += x_step;
		ray->next_vert_y += y_step;
	}
}

void	set_closest_hit(t_ray *ray, float horz_dist, float vert_dist)
{
	if (vert_dist < horz_dist)
	{
		ray->wall_hit_x = ray->vert_hit_x;
		ray->wall_hit_y = ray->vert_hit_y;
		ray->distance = vert_dist;
		ray->was_hit_vertical = 1;
	}
	else
	{
		ray->wall_hit_x = ray->horz_hit_x;
		ray->wall_hit_y = ray->horz_hit_y;
		ray->distance = horz_dist;
		ray->was_hit_vertical = 0;
	}
}

t_cardinals	*choose_texture(t_game *game, t_ray *ray)
{
	if ((ray->was_hit_vertical && ray->vert_hit_is_door) || 
        (!ray->was_hit_vertical && ray->horz_hit_is_door))
    {
        // Use door texture
        return (&game->door_tex);
    }
	if (ray->was_hit_vertical)
	{
		if (ray->ray_angle < M_PI_2 || ray->ray_angle > 3 * M_PI_2)
			return (&game->parse_data.ea);
		else
			return (&game->parse_data.we);
	}
	else
	{
		if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
			return (&game->parse_data.so);
		else
			return (&game->parse_data.no);
	}
}

int	get_texture_x(t_ray *ray)
{
	int		tex_x;

	if (ray->was_hit_vertical)
	{
		tex_x = (int)ray->wall_hit_y % TILESIZE;
		if (ray->ray_angle > M_PI_2 && ray->ray_angle < 3 * M_PI_2)
			tex_x = TILESIZE - tex_x - 1;
	}
	else
	{
		tex_x = (int)ray->wall_hit_x % TILESIZE;
		if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
			tex_x = TILESIZE - tex_x - 1;
	}
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TILESIZE)
		tex_x = TILESIZE - 1;
	return (tex_x);
}

int	get_texture_y(t_cardinals *tex, int height, int y)
{
	int	offset;
	int	tex_y;

	offset = y + (height / 2) - (WINDOW_HEIGHT / 2);
	tex_y = (offset * tex->h) / height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->h)
		tex_y = tex->h - 1;
	return (tex_y);
}

unsigned int	shade_color(unsigned int color, float distance, t_game *game)
{
	float			shade_factor;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	// !ahm ahm
	//? Light intensity = 1 / (1 + k * distance) Where k is a constant
	if (game->light % 2 == 0)
		shade_factor = 1.0f / (1.0f + distance * 0.001f);
	else
		shade_factor = 1.0f / (1.0f + distance * 0.03f);
	
	r = ((color >> 16) & 0xFF) * shade_factor;
	g = ((color >> 8) & 0xFF) * shade_factor;
	b = (color & 0xFF) * shade_factor;
	return ((r << 16) | (g << 8) | b);
}

void	draw_column_strip(t_game *game, t_column_params *p, int height)
{
	int		y;
	int		tex_y;
	char	*pix;
	int		color;

	y = p->top;
	while (y < p->bottom)
	{
		tex_y = get_texture_y(p->texture, height, y);
		pix = p->texture->addr + (tex_y * p->texture->line_length + \
				p->tex_x * (p->texture->bits_per_pixel / 8));
		color = *(unsigned int *)pix;
		put_pixel_in_img(game, p->x + p->i, y, shade_color(color, game->ray.distance, game));
		y++;
	}
}

void draw_door_column_strip(t_game *game, t_column_params *p, int height, t_door *door)
{
    int     y;
    int     tex_y;
    char    *pix;
    int     color;
    
    // For this example, let's use animation_type = 0 (sliding up)
    door->animation_type = 0;
    
    y = p->top;
    while (y < p->bottom)
    {
        // Get texture Y with standard calculation
        tex_y = get_texture_y(p->texture, height, y);
        
        // For sliding up door, offset the texture based on open state
        int offset_y = door->open_state * p->texture->h;
        int adjusted_tex_y = (tex_y + offset_y) % p->texture->h;
        
        // Skip rendering the bottom part of the door that's already slid up
        if (door->animation_type == 0 && tex_y < offset_y * height / p->texture->h)
        {
            // Skip drawing (door is "open" at this part)
            y++;
            continue;
        }
        
        // Get pixel from texture
        pix = p->texture->addr + (adjusted_tex_y * p->texture->line_length + 
                p->tex_x * (p->texture->bits_per_pixel / 8));
        
        color = *(unsigned int *)pix;
        
        // Apply lighting as usual
        put_pixel_in_img(game, p->x + p->i, y, 
            shade_color(color, game->ray.distance, game));
        
        y++;
    }
}
void draw_textured_column(t_game *game, t_ray *ray, int ray_id, int height)
{
    t_column_params params;
    int is_door = 0;
    int door_index = -1;
    
    // Check if this ray hit a door - THIS IS THE CRUCIAL PART YOU MISSED
    if (ray->was_hit_vertical && ray->vert_hit_is_door) 
        is_door = 1;
    else if (!ray->was_hit_vertical && ray->horz_hit_is_door)
        is_door = 1;
        
    params.x = ray_id * RES;
    params.tex_x = get_texture_x(ray);
    
    // Choose texture based on whether this is a door
    if (is_door)
        params.texture = &game->door_tex;
    else
        params.texture = choose_texture(game, ray);
        
    params.top = (WINDOW_HEIGHT / 2) - (height / 2);
    params.bottom = (WINDOW_HEIGHT / 2) + (height / 2);
    
    if (params.top < 0)
        params.top = 0;
    if (params.bottom > WINDOW_HEIGHT)
        params.bottom = WINDOW_HEIGHT;
    
    // If this is a door, find which door was hit
    if (is_door)
    {
        int map_x = floor(ray->wall_hit_x / TILESIZE);
        int map_y = floor(ray->wall_hit_y / TILESIZE);
        
        for (int i = 0; i < game->door_count; i++)
        {
            if (game->doors[i].x == map_x && game->doors[i].y == map_y)
            {
                door_index = i;
                break;
            }
        }
    }
    
    params.i = 0;
    while (params.i < RES)
    {
        // For doors, we'll use a modified draw function
        if (is_door && door_index != -1)
            draw_door_column_strip(game, &params, height, &game->doors[door_index]);
        else
            draw_column_strip(game, &params, height);
        
        params.i++;
    }
}