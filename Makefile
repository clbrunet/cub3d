NAME		=	Cub3D

SRCS		=	srcs/main.c		\
				srcs/get_next_line/get_next_line.c			\
				srcs/get_next_line/get_next_line_utils.c	\
				srcs/utils/initialize.c		\
				srcs/utils/free.c			\
				srcs/utils/fts.c			\
				srcs/utils/angles.c			\
				srcs/utils/map.c			\
				srcs/utils/lines.c			\
				srcs/parsing/base.c			\
				srcs/parsing/elems.c		\
				srcs/parsing/elems2.c		\
				srcs/parsing/check_elems.c	\
				srcs/parsing/map.c			\
				srcs/parsing/check_map.c	\
				srcs/hooks/base.c	\
				srcs/hooks/update.c	\
				srcs/raycasting/base.c				\
				srcs/raycasting/horizontal_hit.c	\
				srcs/raycasting/vertical_hit.c		\
				srcs/raycasting/monster.c			\
				srcs/draw/base.c	\
				srcs/draw/col.c		\
				srcs/draw/col2.c	\
				srcs/draw/bitmap.c	\
				srcs/draw/hud.c


OBJS		=	$(SRCS:.c=.o)

LIBFT		=	libft/libft.a
LIBMLX		=	minilibx_linux/libmlx.a

LIBSFLAGS	=	$(LIBFT) $(LIBMLX) -lXext -lX11 -lm


CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror	\
				-I./libft/ -I./minilibx_linux/ -I./includes/

all			:	$(NAME)

$(LIBFT)	:
				make bonus -C libft/

$(LIBMLX)	:
				make -C minilibx_linux/

$(NAME)		:	$(LIBFT) $(LIBMLX) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIBSFLAGS) -o $(NAME)

bonus		:	$(NAME)

clean		:
				make clean -C libft/
				make clean -C minilibx_linux/
				rm -f $(OBJS)

fclean		:	clean
				make fclean -C libft/
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
