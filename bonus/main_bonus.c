/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfhad <hfhad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:00:51 by hfhad             #+#    #+#             */
/*   Updated: 2025/05/23 15:48:23 by hfhad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

int	close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	destroy_img(game);
	mlx_destroy_image(game->mlx, game->minimap.minimap_img);
	mlx_destroy_image(game->mlx, game->img_ptr);
	free_parse_data(game);
	exit(1);
}

int	game_setup(t_game *game)
{
	init_logic(game);
	init_player(&game->player, game);
	init_minimap(game);
	game->load += init_door(game);
	game->load += init_light(game);
	if (game->load)
		return (destroy_img(game), 1);
	return (0);
}

void	game_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, combined_update, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 4, 1, pressed, game);
	mlx_hook(game->win, 5, 1, released, game);
	mlx_hook(game->win, 6, 1, mouse_movement_handeling, game);
}

void	print_how_to_use(void)
{
	printf("\n");
	printf("  " ORANGE1 " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗" RESET "\n");
	printf("  " ORANGE2 "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗" RESET "\n");
	printf("  " ORANGE3 "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║" RESET "\n");
	printf("  " ORANGE4 "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║" RESET "\n");
	printf("  " ORANGE1 "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝" RESET "\n");
	printf("  " ORANGE5 " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝" RESET "\n");
	printf("                    " TITLE_CLR "BONUS EDITION" RESET "\n");
	printf("\nUsage: ./cub3D_bonus <map.cub>\n\n");
	printf(BOLD "Movement Controls:" RESET "\n");
	printf("  W A S D      → Move around\n");
	printf("  ← →          → Rotate view\n");
	printf("  " GREEN "Mouse drag   → Look around (click & drag)" RESET "\n");
	printf("  ESC          → Exit\n\n");
	printf(BOLD "Minimap Controls:" RESET "\n");
	printf("  " BLUE "M            → Toggle minimap on/off" RESET "\n");
	printf("  " BLUE "↑ ↓          → Resize minimap" RESET "\n\n");
	printf(BOLD "Special Features:" RESET "\n");
	printf("  " YELLOW "F            → Toggle flashlight" RESET "\n");
	printf("  " PURPLE "B            → Show door button" RESET "\n");
	printf("  " PURPLE "SPACE        → Activate door button" RESET "\n");
	printf("\nEnhanced maze experience with interactive elements! 🎮🗺️\n\n");
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (printf("Error: mlx initialization failed\n"), 1);
	game.load = 0;
	game.parse_data.no.ptr = NULL;
	game.parse_data.so.ptr = NULL;
	game.parse_data.we.ptr = NULL;
	game.parse_data.ea.ptr = NULL;
	game.parse_data.fd = -1;
	if (parsing(ac, av, &game) != 0)
		return (free_parse_data(&game), 1);
	close(game.parse_data.fd);
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3d");
	game.img_ptr = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img_ptr, \
				&game.bits_per_pixel, &game.line_length, &game.endian);
	if (game_setup(&game))
		return (destroy_img(&game), exit(1), 1);
	print_how_to_use();
	game_hooks(&game);
	mlx_loop(game.mlx);
}
