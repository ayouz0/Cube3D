NAME = cube

FLAGS = -Wall -Werror -Wextra

LINKING = -lmlx -framework OpenGL -framework AppKit 

SRC = main.c player.c input.c map.c raycasting.c settings.c update.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

%.o: %.c header.h
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