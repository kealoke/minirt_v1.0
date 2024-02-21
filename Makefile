NAME = minirt
CC = gcc
CFLAGS =  -MMD -MP -g
OPTION = -lmlx -framework OpenGL -framework Appkit
OBJ_DIR = ./objs
SRC_DIR = ./input ./gnl ./render

SRCS = main.c \
		get_next_line.c get_next_line_utils.c \
 		input_check.c inputParse.c inputRead.c inputSet.c inputSetUtiles.c inputSetObjs.c inputUtils.c \
		render.c mlx.c obj_list.c colorCalc_1.c colorCalc_2.c vecCalc_1.c vecCalc_2.c \
		plane.c sphere.c cylinder.c intersection.c reflection.c
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
