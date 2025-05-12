NAME = cub3D

FLAGS = -Wall -Werror -Wextra

LINKING = -lmlx -framework OpenGL -framework AppKit# -fsanitize=address

UTILS = utils/ft_strchr.c utils/ft_strdup.c utils/ft_strncmp.c utils/ft_strlen.c \
		utils/get_next_line.c utils/get_next_line_utils.c

HEADERS = header.h engine/engine.h parsing/parsing.h utils/utils.h utils/get_next_line.h

SRC = main.c engine/player.c engine/input.c engine/map.c \
		engine/raycasting.c engine/settings.c engine/update.c \
		parsing/parser.c parsing/loading_cardinals.c \
		parsing/loading_map_utils.c parsing/loading_map.c \
		parsing/parsing_cardinals_and_colors.c engine/draw.c \
		engine/ray_hit.c engine/ray_draw.c \
		parsing/map_validation.c parsing/map_validation_helpers.c \
		parsing/loading_data_helpers.c $(UTILS)

OBJ = ${SRC:.c=.o}

all: $(NAME)

%.o: %.c $(HEADERS)
	cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) 
	cc $(FLAGS) $(OBJ) -o $(NAME) $(LINKING)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	@echo "🧹 Object files removed."

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@echo "🗑️ Executables removed."

re: fclean all

.PHONY: clean