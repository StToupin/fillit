CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

NAME = fillit

OBJ = input.o coordinates.o tetriminos.o solve.o main.o
SRC = $(OBJ:.o=.c)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norminette:
	norminette fillit.h $(SRC)
