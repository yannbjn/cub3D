NAME        =   cub3D

CC          =   cc

LIBS        =   /inc

FLAG        =   -g3 -Wall -Wextra -Werror

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

MLX_FILE	=	libmlx.a

MLX_FLAGS	=	-lX11 -lXext

MLX_PATH	=	./minilibx-linux

MLX_LIB		=	$(MLX_PATH)/$(MLX_FILE)

MLX_EX		=	$(MLX_LIB) $(MLX_FLAGS)

C_FILES     =   srcs/main.c \
				srcs/errors/ft_error.c \
				srcs/raycast/raycaster.c \
				srcs/raycast/raycast_utils.c \
				srcs/inits/inits.c \
				srcs/inits/inits2.c \
				srcs/parsing/parser.c \
				srcs/parsing/parser2.c \
				srcs/parsing/parser3.c \
				srcs/parsing/parser4.c \
				srcs/movement/mov.c \
				srcs/movement/mov2.c

OBJ_DIR     =   builds

OBJS        =   $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.o))

DEPS        =   $(OBJS:.o=.d)

all:        $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/srcs/parsing \
			  $(OBJ_DIR)/srcs/errors \
			  $(OBJ_DIR)/srcs/raycast \
			  $(OBJ_DIR)/srcs/inits \
			  $(OBJ_DIR)/srcs/movement

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(FLAG) -MMD -MP -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(MLX_LIB):
	make -C $(MLX_PATH)

$(NAME):    $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(LIBFT_LIB) $(MLX_EX) -o $(NAME) -lm

clean:
	make clean -C $(MLX_PATH)
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJ_DIR) $(DEPS)

fclean:     clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

re:         fclean all

-include $(DEPS)

.PHONY:     all clean fclean re