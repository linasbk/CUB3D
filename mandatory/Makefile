CC := cc
NAME := cub3D
CFLAGS := -Wall -Wextra -Werror -Ofast #-g -fsanitize=address
SRCS =	main.c utilis/gnl.c utilis/utils.c utilis/ft_split.c utilis/ft_atoi.c \
			parsing/parsing.c parsing/errors.c parsing/valide_color.c parsing/valide_file.c parsing/valide_map.c raycasting/raycasting.c \
			init/init.c  minimap.c  utilis/keyhook.c draw_line.c init/sky_floor.c\

OBJ = $(SRCS:.c=.o)
MLX        := libs/libmlx.a
LIBS    := -lglfw -L/Users/lsabik/.brew/opt/glfw/lib
# LIBS    := -lglfw -L/Users/nobuahidi/.brew/opt/glfw/lib

OBJS := $(SRCS:.c=.o)

%.o: %.c includes/cub3d.h 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) ${LIBFT} -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
