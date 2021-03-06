#:::: INFO :::::::::::::::::::::::::::::::::::::::::::::::::::
NAME			=	miniRT

INCLUDES		=	-I ./includes/

HEADERS			=	./includes/get_next_line.h	\
					./includes/maths.h			\
					./includes/matrix.h			\
					./includes/minirt.h			\
					./includes/objects.h		\
					./includes/ray.h			\
					./includes/tuple.h

VPATH			=	./srcs/				\
					./srcs/get_nextline/\
					./mlx/mlx_linux/	\
					./libft/includes/	\
					./srcs/maths/		\
					./srcs/parser/		\
					./srcs/render/


#:::: FILES ::::::::::::::::::::::::::::::::::::::::::::::::::
SRCS_NAME		=	main.c		\
					init.c		\
					view.c		\
					keys.c		\
					exception.c

GNL_SRCS		=	get_next_line.c			\
                 	get_next_line_utils.c

MATH_SRCS		=	collations.c			\
					ft_degrees_to_radians.c \
					ft_pow.c				\
					ft_quadratic_roots.c	\
					tuple.c					\
					vector.c				\
					matrix.c

RENDER_SRCS		=	new_image.c			\
					info.c				\
					ray.c				\
					computations.c		\
					color.c				\
					light.c

OBJECTS_SRCS	=	intersections.c		\
					normal.c			\
					resize.c

PARSER_SRCS		=	converter_file.c	\
					new_camera.c		\
					new_ambient.c		\
					new_light.c			\
					new_object.c		\
					utils.c

LIBRARY			=	libft/libft.a

#:::: PATHS ::::::::::::::::::::::::::::::::::::::::::::::::::
LIBFT_PATH		=	./libft/
SRCS_PATH		=	./srcs/
GNL_PATH		=	./srcs/get_nextline/
MATH_PATH		=	./srcs/maths/
RENDER_PATH		=	./srcs/render/
OBJECTS_PATH	=	./srcs/render/objects/
PARSER_PATH		=	./srcs/parser/
OBJS_DIR		=	./objs/


OBJS_NAME		=	$(SRCS_NAME:.c=.o)	\
					$(GNL_SRCS:.c=.o)	\
					$(MATH_SRCS:.c=.o)	\
					$(PARSER_SRCS:.c=.o)\
					$(RENDER_SRCS:.c=.o)\
					$(OBJECTS_SRCS:.c=.o)

SRCS			=	$(addprefix $(SRCS_PATH), $(SRCS_NAME)) 	\
					$(addprefix $(GNL_PATH), $(GNL_SRCS))		\
					$(addprefix $(MATH_PATH), $(MATH_SRCS))		\
					$(addprefix $(PARSER_PATH), $(PARSER_SRCS))	\
					$(addprefix $(RENDER_PATH), $(RENDER_SRCS)) \
					$(addprefix $(OBJECTS_PATH), $(OBJECTS_SRCS))

OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_NAME))

FLAGS	= -Wall -Wextra -Werror

OS_NAME	= $(shell uname -s | tr A-Z a-z)
ifeq	($(OS_NAME), linux)
			OBJ_MLX_FLAGS	= -I/usr/include -Imlx_linux -O3 -lXext -lX11
			LINK_MLX_FLAGS	= -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
			MLX_PATH		= ./mlx/mlx_linux/
			MLX_LIBRARY		= mlx/mlx_linux/libmlx_Linux.a
			FLAGS			+= -D LINUX=1
else
			OBJ_MLX_FLAGS	= -Imlx
			LINK_MLX_FLAGS	= -Lmlx -lmlx -framework OpenGL -framework AppKit
			MLX_PATH		= ./mlx/mlx_mac/
			MLX_LIBRARY		= mlx/mlx_mac/libmlx.a
			FLAGS			+= -D DARWIN=1
endif

#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
.PHONY:		all clean fclean re
#			::::::::::::::::::::::::::::::::::::::::::::::::::
#			::	all		::	compiles files with clang++		::
#			::	clean	::	removes object files			::
#			::	fclean	::	removes object files & program	::
#			::::::::::::::::::::::::::::::::::::::::::::::::::

all: 			$(NAME)

$(NAME):		$(OBJS)
				@$(MAKE)	-C			$(LIBFT_PATH)
				@$(MAKE)	-C			$(MLX_PATH)
				@$(CC)  $(FLAGS) $(OBJS)	$(LIBRARY) $(MLX_LIBRARY) $(LINK_MLX_FLAGS) -o $(NAME)

$(OBJS):		$(SRCS) $(HEADERS)
				@gcc $(FLAGS) $(INCLUDES)	-c	$(SRCS) $(OBJ_MLX_FLAGS)
				@mkdir	-p				$(OBJS_DIR)
				@mv		$(OBJS_NAME)	$(OBJS_DIR)

clean:
			@rm -rf obj/
			@make clean -C $(MLX_PATH)
			@make clean -C libft/

fclean:		clean
			@rm -rf $(NAME)
			@make fclean -C libft/

re:			fclean all