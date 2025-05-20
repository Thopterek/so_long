NAME = libftprintf.a
# Source files for ft_printf
SRCS = \
		ft_printf.c \
		ft_uns_itoa.c \
		ft_hex_itoa.c \
		ft_ptr_itoa.c \
		get_next_line.c
# Object files
OBJS = $(SRCS:.c=.o)
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
# Path to libft directory
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
# The rule to build the project
all: $(LIBFT) $(NAME)
# Compiling libft first
$(LIBFT):
	make -C $(LIBFT_DIR)
# Compiling ft_printf
$(NAME): $(OBJS) $(LIBFT)
	ar rcs $(NAME) $(OBJS) $(LIBFT_DIR)/*.o
# Cleaning object files in both projects
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
# Full clean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
# Rebuild everything
re: fclean all

.PHONY: all clean fclean re