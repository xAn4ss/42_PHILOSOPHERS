SRC = philo.c\
		Utils_1.c\
		supervisors.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)
	@gcc $(FLAGS) $(SRC) -o $(NAME) 

clean :
	@rm -rf $(OBJ)
	
fclean : clean
	@rm -rf $(NAME)

re : fclean all	