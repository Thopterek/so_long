NAME = so_long

CC = cc
CFLAGS = -Wextra -Wall -Werror
LIBMLX_DIR = ./MLX42
LIBLIB_DIR = ./lib_pri_get

HEADERS = -I $(LIBMLX_DIR)/include -I $(LIBLIB_DIR)/include
MLX = $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIB = $(LIBLIB_DIR)/libftprintf.a

SRCS = \
		0main.c \
		1map.c \
		2map_utility.c \
		3graphic.c \
		4graphic_utility.c \
		5game.c \
		6game_utility.c \
		global_utility.c

OBJS = $(SRCS:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make -C $(LIBLIB_DIR)

mlx:
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	@make -C $(LIBMLX_DIR)/build -j4

$(NAME): $(OBJS) | $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIB) $(HEADERS) \
		-framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C $(LIBMLX_DIR)/build clean
	make -C $(LIBLIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBLIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re