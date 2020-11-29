NAME		=	Cub3D

SRCS		=	srcs/main.c									\
				srcs/get_next_line/get_next_line.c			\
				srcs/get_next_line/get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

LIBFT		=	libft/libft.a
LIBMLX		=	minilibx_linux/libmlx.a

LIBSFLAGS	=	$(LIBFT) $(LIBMLX) -lXext -lX11 -lm -lbsd


CC			=	clang-9
CFLAGS		=	-Wall -Wextra -Werror -I./includes/ -I./libft/ -I./minilibx_linux/

all			:	$(NAME)

$(LIBFT)	:
				make -C libft/

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
