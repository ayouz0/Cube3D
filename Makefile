NAME = cube

FLAGS = -Wall -Werror -Wextra

LINKING = -lmlx -framework OpenGL -framework AppKit 

HEADERS = header.h engine/engine.h parsing/parsing.h

SRC = main.c engine/player.c engine/input.c engine/map.c \
		engine/raycasting.c engine/settings.c engine/update.c

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