#	PROGRAM_NAMES
NAME = cub3D

#	FLAG_COMPILATION
CC = clang
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I $(HEADER_DIR) -I $(FT) -I $(MLX)
FRAME_MAC = -framework OpenGL -framework AppKit -lz

MLX = ./mlx_mac/
MLX_LINK = -L $(MLX) -l mlx $(FRAME_MAC)

FT = ./libft/
FT_INC = ./libft/libft.h
FT_LINK = -L $(FT) -l ft

#	HEADERS
HEADER_LIST = cube_3d.h
HEADER_DIR = ./include/
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LIST))


#	SOURCE
SRC_DIR = ./source/
SRC_FILE =	control.c				\
			control_borders.c		\
			draw_walls.c			\
			initialize.c			\
			main.c					\
			parse.c					\
			parse_map.c				\
			parse_settings.c		\
			raycasting.c			\
			utils.c
SRC_LIST = $(addprefix $(SRC_CORE_DIR), $(SRC))


#	OBJECT_FILES
OBJ_DIR = ./obj/
OBJ_DIR_NAME = obj
OBJ_FILE = $(patsubst %.c, %.o, $(SRC_FILE))
OBJ_LIST = $(addprefix $(OBJ_DIR), $(OBJ_FILE) )


#	COLORS
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
END = \033[0m


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_LIST)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_LIST) $(MLX_LINK) $(FT_LINK) -o $(NAME)
	@echo "$(GREEN) $(NAME) created. $(END)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR_NAME)
	@echo "$(BLUE) Object files directory was created. $(END)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

clean:
	@rm -rf $(OBJ_LIST)
	@rm -rf $(OBJ_DIR_NAME)
	@echo "$(RED) Object files were deleted. $(END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED) $(NAME) was deleted. $(END)"

re: fclean all


.PHONY: all bonus clean fclean re