NAME = fractol
BNAME = fractol_bonus
FLAGS = -Wall -Wextra -Werror -O3 -march=native -ffast-math

SRC = src/mandatory/fractol.c src/mandatory/keyhook.c src/mandatory/util.c
OBJ = $(SRC:%.c=obj/%.o)

BSRC = src/bonus/fractol_bonus.c src/bonus/keyhook_bonus.c src/bonus/util_bonus.c
BOBJ = $(BSRC:%.c=obj/%.o)

all: $(NAME)

bonus: $(BNAME)

obj/%.o: %.c
	mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@ -I inc -I ccmlx

$(NAME): $(OBJ)
	cc $^ -o $@ -L ccmlx -l mlx -l Xext -l X11 -l m

$(BNAME): $(BOBJ)
	cc $^ -o $@ -L ccmlx -l mlx -l Xext -l X11 -l m

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re

