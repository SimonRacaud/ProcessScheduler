##
## @file Makefile
## @author simon.racaud 33287430 srac0005@student.monash.edu
## createdAt: 11:26:47 AM Thu Sep 29 2022
## updatedAt: 11:26:47 AM Thu Sep 29 2022
##

SRC1 = 	task1-33287430.c	\
		file.c				\
		arg.c

OBJ1 = $(SRC1:.c=.o)

CFLAGS = -Wall -Wextra -Werror -W -I./

NAME1 = task1

all: $(NAME1)

$(NAME1): $(OBJ1)
	@$(CC) $(OBJ1) -o $(NAME1)

clean:
	@$(RM) -f $(OBJ1)

fclean: clean
	@$(RM) -f $(NAME1)

re: fclean all

debug: CFLAGS += -g
debug: clean all

.PHONY: clean fclean re debug