NAME = fractol
BNAME = fractol_bonus
FLAGS = -Wall -Wextra -Werror -O3 -march=native -ffast-math
MLX = mlx/libmlx.a

SRC = src/mandatory/fractol.c src/mandatory/keyhook.c src/mandatory/util.c \
	  src/helper.c
OBJ = $(SRC:%.c=obj/%.o)

BSRC = src/bonus/fractol_bonus.c src/bonus/fractals_bonus.c \
	   src/bonus/keyhook_bonus.c src/bonus/util_bonus.c src/helper.c
BOBJ = $(BSRC:%.c=obj/%.o)

all: $(NAME) $(MLX)

obj/%.o: %.c
	mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@ -Iinc -Imlx

$(MLX):
	make -C mlx

$(NAME): $(OBJ)
	cc $^ -o $@ -Lmlx -lmlx -lXext -lX11 -lm

bonus: $(BNAME)

$(BNAME): $(BOBJ)
	cc $^ -o $@ -Lmlx -lmlx -lXext -lX11 -lm

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all bonus

.PHONY: all clean fclean re

