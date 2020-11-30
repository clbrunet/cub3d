NAME		=	Cub3D

SRCS		=	srcs/main.c		\
				srcs/debug.c	\
				srcs/get_next_line/get_next_line.c			\
				srcs/get_next_line/get_next_line_utils.c	\
				srcs/initialize.c		\
				srcs/free.c				\
				srcs/errors/parsing.c	\
				srcs/parsing/scene.c	\
				srcs/parsing/utils.c

OBJS		=	$(SRCS:.c=.o)

LIBFT		=	libft/libft.a
LIBMLX		=	minilibx_linux/libmlx.a

LIBSFLAGS	=	$(LIBFT) $(LIBMLX) -lXext -lX11 -lm -lbsd


CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address \
				-I./libft/ -I./minilibx_linux/ -I./includes/

all			:	$(NAME)

$(LIBFT)	:
				make bonus -C libft/

$(LIBMLX)	:
				make -C minilibx_linux/

$(NAME)		:	$(LIBFT) $(LIBMLX) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIBSFLAGS) -o $(NAME)

clean		:
				make clean -C libft/
				make clean -C minilibx_linux/
				rm -f $(OBJS)

fclean		:	clean
				make fclean -C libft/
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
