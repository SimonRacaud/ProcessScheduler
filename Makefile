##
## @file Makefile
## @author simon.racaud 33287430 srac0005@student.monash.edu
## createdAt: 11:26:47 AM Thu Sep 29 2022
## updatedAt: 11:26:47 AM Thu Sep 29 2022
##

SRC = 	file.c				\
		arg.c				\
		simulator.c 		\
		list.c				\
		common.c			\

SRC1 = 	$(SRC) task1-33287430.c
SRC2 = 	$(SRC) task2-33287430.c
SRC3 = 	$(SRC) task3-33287430.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)

CFLAGS = -Wall -Wextra -Werror -W -I./

NAME1 = task1
NAME2 = task2
NAME3 = task3

all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1): $(OBJ1)
	@$(CC) $(OBJ1) -o $(NAME1)

$(NAME2): $(OBJ2)
	@$(CC) $(OBJ2) -o $(NAME2)

$(NAME3): $(OBJ3)
	@$(CC) $(OBJ3) -o $(NAME3)

clean:
	@$(RM) -f $(OBJ1) $(OBJ2) $(OBJ3)

fclean: clean
	@$(RM) -f $(NAME1) $(NAME2) $(NAME3)

re: fclean all

debug: CFLAGS += -g
debug: clean all

.PHONY: clean fclean re debug