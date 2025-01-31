NAME = pipex

PROG =	ft_split\
		get_next_line_utils\
		get_next_line\
		lib\
		path\
		pipex\
		utils\


SRC = $(addsuffix .c, $(PROG))

OBJ = $(addsuffix .o, $(PROG))

CC = cc

#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall

all :		$(NAME)

$(NAME) :	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

%.o :		%.c
			$(CC) -c $< $(CFLAGS) -o $@

clean :
			rm -f $(OBJ)

fclean : 	clean
			rm -f $(NAME)

re :		fclean all

a :			all clean

.PHONY :	all clean fclean re a
