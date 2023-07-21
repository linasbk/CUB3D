CC := cc
NAME := cub3D
CFLAGS := -Wall -Wextra -Werror -Ofast #-g -fsanitize=address
SRCS =	src/main.c src/utilis/gnl.c src/utilis/utils.c src/utilis/ft_split.c src/render/sprite_utils2.c src/utilis/ft_atoi.c src/raycasting/raycasting_utils.c src/utilis/utils_2.c src/render/sprite_utils.c\
			src/parsing/parsing.c src/parsing/errors.c src/parsing/valide_color.c src/parsing/valide_file.c src/parsing/valide_map.c src/raycasting/raycasting.c src/render/render_wall.c\
			src/init/init.c  src/minimap.c src/utilis/keyhook.c src/init/sky_floor.c src/init/fullmap.c src/init/fullmaputils.c src/utilis/texture_utils.c src/render/sprites.c draw_line.c src/utilis/keyhookutil.c\

OBJ = $(SRCS:.c=.o)
MLX        := libs/libmlx.a
LIBS    := -lglfw -L/Users/lsabik/.brew/opt/glfw/lib
# LIBS    := -g -lglfw -L/Users/nouahidi/.brew/opt/glfw/lib

OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c includes/cub3d.h includes/macros.h
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) ${LIBFT} -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
