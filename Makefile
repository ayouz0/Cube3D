NAME = cub3D

FLAGS = -Wall -Werror -Wextra

LINKING = -lmlx -framework OpenGL -framework AppKit -fsanitize=address

LIBFT = libft/libft.a

HEADERS = header.h engine/engine.h parsing/parsing.h

SRC = main.c engine/player.c engine/input.c engine/map.c \
		engine/raycasting.c engine/settings.c engine/update.c \
		parsing/parser.c parsing/loading_cardinals.c \
		parsing/loading_map_utils.c parsing/loading_map.c \
		parsing/parsing_cardinals_and_colors.c engine/draw.c

OBJ = ${SRC:.c=.o}

all: libft $(NAME)

%.o: %.c $(HEADERS)
	cc $(FLAGS) -c $< -o $@

libft:
	make -C libft

$(NAME): $(OBJ) 
	cc $(FLAGS) $(OBJ) -o $(NAME) $(LINKING) $(LIBFT)

clean:
	make clean -C libft
	rm -f $(OBJ) $(OBJ_BONUS)
	@echo "🧹 Object files removed."

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(BONUS_NAME)
	@echo "🗑️ Executables removed."

re: fclean all

.PHONY: clean libft