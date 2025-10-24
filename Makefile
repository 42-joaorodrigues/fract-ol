NAME = fractol
BNAME = fractol_bonus
FLAGS = -Wall -Wextra -Werror -O3 -march=native -ffast-math

SRC = src/mandatory/fractol.c src/mandatory/keyhook.c src/mandatory/util.c \
	  src/helper.c
OBJ = $(SRC:%.c=obj/%.o)

BSRC = src/bonus/fractol_bonus.c src/bonus/fractals_bonus.c \
	   src/bonus/keyhook_bonus.c src/bonus/util_bonus.c src/helper.c
BOBJ = $(BSRC:%.c=obj/%.o)

all: $(NAME)

bonus: $(BNAME)

obj/%.o: %.c
	mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@ -Iinc -Iccmlx

$(NAME): $(OBJ)
	cc $^ -o $@ -Lccmlx -lmlx -lXext -lX11 -lm

$(BNAME): $(BOBJ)
	cc $^ -o $@ -Lccmlx -lmlx -lXext -lX11 -lm

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all bonus

.PHONY: all clean fclean re

