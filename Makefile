CC := cc
NAME := cub3d
SRC_NAME =	main.c utilis/gnl.c utilis/utils.c utilis/ft_split.c utilis/ft_atoi.c \
			parsing/parsing.c parsing/errors.c parsing/valide_color.c parsing/valide_file.c \
			init/init.c \

OBJ = $(SRC_NAME:.c=.o)

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

all: ${NAME}
$(NAME): $(OBJ)
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	$(CC) $(OBJ) -lmlx -framework OpenGL -ofast -framework AppKit -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✔️"

%.o: %.c fdf.h
	$(CC) -fno-signed-zeros -mtune=intel -Ofast -march=native -fno-trapping-math -Wall -Wextra -Werror  -Imlx -c $< -o $@


clean:
	@ ${RM} *.o */*.o */*/*.o
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean: clean
	@ ${RM} ${NAME}
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
re: fclean all