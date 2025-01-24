NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c) 
OBJ = $(SRC:.c=.o)
INCLUDES = -I.

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re