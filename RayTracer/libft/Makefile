#:::::::::::::::::::::::::::::::::::::::::::	INFO
NAME =			libft.a
#:::::::::::::::::::::::::::::::::::::::::::	SOURCES

HEADER =		libft.h

FILES =			ft_putnbr_fd.c		ft_split.c\
				ft_strdup.c			ft_strncmp.c\
				ft_substr.c			ft_atoi.c\
				ft_itoa.c			ft_strlen.c\
				ft_strchr.c			ft_strjoin.c\
				ft_strmapi.c		ft_isempty.c\
				ft_strrchr.c		ft_memcmp.c\
				ft_atod.c			ft_sigmlen.c\
				ft_isdigit.c		ft_memset.c\
				ft_calloc.c			ft_strtrim.c\
				ft_dtoa.c

INCLUDES =		-I includes/
FILES_DIR =		./srcs/
SRCS = 			$(addprefix $(FILES_DIR), $(FILES))
OBJS =			$(addprefix objects/, $(FILES:.c=.o))

#:::::::::::::::::::::::::::::::::::::::::::	OPTIONS
CFLAGS =		-Wall -Wextra -Werror -g


#:::::::::::::::::::::::::::::::::::::::::::	RULES
.PHONY =		all clean fclean re

all:			objects $(NAME)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $?
				@echo "libft compiled."
				@make clean

objects :
				@mkdir $@

objects/%.o :	srcs/%.c
			    @gcc $(FLAGS) $(INCLUDES) -c $< -o $@

#:::::::::::::::::::::::::::::::::::::::::::	CLEAN
clean:
				@rm -rf objects/

fclean:			clean
				@rm -rf $(NAME)

re:				fclean all
