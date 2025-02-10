NAME = pipex

PROG =	ft_printf\
		ft_printnb\
		ft_split\
		get_next_line_utils\
		get_next_line\
		heredoc\
		lib\
		path\
		pipex\
		utils\


SRC = $(addsuffix .c, $(PROG))

OBJ = $(addsuffix .o, $(PROG))

CC = cc

CFLAGS = -Wall -Wextra -Werror

all :		$(NAME)

$(NAME) :	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

%.o :		%.c
#			$(CC) -c $< -o $@
			$(CC) -c $< $(CFLAGS) -o $@

clean :
			rm -f $(OBJ)

fclean : 	clean
			rm -f $(NAME)

re :		fclean all

a :			all clean

.PHONY :	all clean fclean re a
