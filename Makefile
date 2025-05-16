NAME = cub3D
BONUS_NAME = cub3D_bonus

FLAGS = -Wall -Werror -Wextra #-fsanitize=address
LINKING = -lmlx -framework OpenGL -framework AppKit

UTILS_MANDATORY = mandatory/utils/ft_strchr.c mandatory/utils/ft_strdup.c \
	mandatory/utils/ft_strncmp.c mandatory/utils/ft_strlen.c \
	mandatory/utils/get_next_line.c mandatory/utils/get_next_line_utils.c

UTILS_BONUS = bonus/utils/ft_strchr.c bonus/utils/ft_strdup.c \
	bonus/utils/ft_strncmp.c bonus/utils/ft_strlen.c \
	bonus/utils/get_next_line.c bonus/utils/get_next_line_utils.c

HEADERS_MANDATORY = mandatory/header.h mandatory/engine/engine.h \
	mandatory/parsing/parsing.h mandatory/utils/utils.h \
	mandatory/utils/get_next_line.h

HEADERS_BONUS = bonus/header.h bonus/engine/engine.h \
	bonus/parsing/parsing.h bonus/utils/utils.h \
	bonus/utils/get_next_line.h bonus/minimap_bonus/minimap_bonus.h

SRC_MANDATORY = mandatory/main.c mandatory/engine/player.c \
	mandatory/engine/input.c mandatory/engine/map.c \
	mandatory/engine/raycasting.c mandatory/engine/settings.c \
	mandatory/engine/update.c mandatory/parsing/parser.c \
	mandatory/parsing/loading_cardinals.c \
	mandatory/parsing/loading_map_utils.c \
	mandatory/parsing/loading_map.c \
	mandatory/parsing/parsing_cardinals_and_colors.c \
	mandatory/engine/draw.c mandatory/engine/ray_hit.c \
	mandatory/engine/ray_draw.c mandatory/parsing/map_validation.c \
	mandatory/parsing/map_validation_helpers.c \
	mandatory/parsing/loading_data_helpers.c \
	$(UTILS_MANDATORY)

SRC_BONUS = bonus/main.c bonus/engine/player.c \
	bonus/engine/input.c bonus/engine/map.c \
	bonus/engine/raycasting.c bonus/engine/settings.c \
	bonus/engine/update.c bonus/parsing/parser.c \
	bonus/parsing/loading_cardinals.c \
	bonus/parsing/loading_map_utils.c \
	bonus/parsing/loading_map.c \
	bonus/parsing/parsing_cardinals_and_colors.c \
	bonus/engine/draw.c bonus/engine/ray_hit.c \
	bonus/engine/ray_draw.c bonus/parsing/map_validation.c \
	bonus/parsing/map_validation_helpers.c \
	bonus/parsing/loading_data_helpers.c \
	bonus/minimap_bonus/minimap_bonus.c \
	bonus/minimap_bonus/minimap_init_bonus.c \
	bonus/minimap_bonus/mouse_hook_bonus.c \
	$(UTILS_BONUS)

OBJ_MANDATORY = ${SRC_MANDATORY:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ_MANDATORY)
	cc $(FLAGS) $(OBJ_MANDATORY) -o $(NAME) $(LINKING)

$(BONUS_NAME): $(OBJ_BONUS)
	cc $(FLAGS) $(OBJ_BONUS) -o $(BONUS_NAME) $(LINKING)

%.o: %.c $(HEADERS_MANDATORY) $(HEADERS_BONUS)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_MANDATORY) $(OBJ_BONUS)
	@echo "🧹 Object files removed."

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@echo "🗑️ Executables removed."

re: fclean all

.PHONY: all clean fclean re bonus
