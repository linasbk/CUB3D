CC := cc
NAME := cub3D
FLAGS := -Wall -Wextra -Werror -fsanitize=address
SRCS =	main.c utilis/gnl.c utilis/utils.c utilis/ft_split.c utilis/ft_atoi.c \
			parsing/parsing.c parsing/errors.c parsing/valide_color.c parsing/valide_file.c parsing/valide_map.c \
			init/init.c \

OBJ = $(SRCS:.c=.o)
MLX        := libs/libmlx.a
LIBS    := -lglfw -L/Users/lsabik/.brew/opt/glfw/lib 


OBJS := $(SRCS:.c=.o)

%.o: %.c include/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) ${LIBFT} -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
