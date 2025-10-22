NAME = fractol
FLAGS = -Wall -Wextra -Werror -O3 -march=native -ffast-math
SRC = src/fractol.c src/util.c
OBJ = $(SRC:%.c=obj/%.o)

all: $(NAME)

obj/%.o: %.c
	mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@ -I inc -I mlx

$(NAME): $(OBJ)
	cc $^ -o $@ -L mlx -l mlx -l Xext -l X11 -l m

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

