NAME = minirt
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
OPTION = -lmlx -framework OpenGL -framework Appkit
OBJ_DIR = ./objs
SRC_DIR = ./input ./gnl ./render

SRCS = main.c \
		get_next_line.c get_next_line_utils.c \
 		inputCheck.c inputParse.c inputRead.c inputSet.c inputSetObjs.c inputUtils.c \
		draw.c mlx.c obj_list.c color_calc.c vec_calc.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

LIBFT	=	./libft/libft.a

vpath %.c $(SRC_DIR)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OPTION) $(LIBFT) $^ -o $@ -fsanitize=address

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
