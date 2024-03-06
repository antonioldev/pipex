NAME 	= 	pipex
CC 		= 	cc
DEPS 	= 	pipex.h
FLAGS 	= 	-Wall -Wextra -Werror -g
SRC 	= 	main.c ft_utils.c ft_split.c \
			ft_parse.c ft_clean.c ft_execute.c \
			ft_parse_folder.c ft_strjoin.c
OBJ 	= 	$(SRC:.c=.o)
RM 		= 	rm -f

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean :
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re