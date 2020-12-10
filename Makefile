NAME		=	Cub3D

SRCS		=	srcs/main.c		\
				srcs/debug.c	\
				srcs/get_next_line/get_next_line.c			\
				srcs/get_next_line/get_next_line_utils.c	\
				srcs/utils/free.c			\
				srcs/utils/ft_atoitrim.c	\
				srcs/utils/angles.c			\
				srcs/utils/map.c			\
				srcs/utils/lines.c			\
				srcs/parsing/base.c			\
				srcs/parsing/elems.c		\
				srcs/parsing/check_elems.c	\
				srcs/parsing/map.c			\
				srcs/parsing/check_map.c	\
				srcs/minilibx/base.c	\
				srcs/minilibx/draw.c	\
				srcs/raycasting/base.c				\
				srcs/raycasting/horizontal_hit.c	\
				srcs/raycasting/vertical_hit.c		\

OBJS		=	$(SRCS:.c=.o)

LIBFT		=	libft/libft.a
LIBMLX		=	minilibx_linux/libmlx.a

LIBSFLAGS	=	$(LIBFT) $(LIBMLX) -lXext -lX11 -lbsd -lm


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


cl			:
				rm -f $(OBJS)
clean		:
				make clean -C libft/
				make clean -C minilibx_linux/
				rm -f $(OBJS)

fcl			:	cl
				rm -f $(NAME)

fclean		:	clean
				make fclean -C libft/
				rm -f $(NAME)

r			:	fcl all

re			:	fclean all

.PHONY		:	all clean fclean re
