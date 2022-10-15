##
## @file Makefile
## @author simon.racaud
## createdAt: 11:26:47 AM Thu Sep 29 2022
## updatedAt: 11:26:47 AM Thu Sep 29 2022
##

SRC = 	src/file.c				\
		src/arg.c				\
		src/simulator.c 		\
		src/list.c				\
		src/common.c			\

SRC1 = 	$(SRC) src/main_fcfs.c
SRC2 = 	$(SRC) src/main_rr.c
SRC3 = 	$(SRC) src/main_edf.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)

CFLAGS = -Wall -Wextra -Werror -W -I./include

NAME1 = fcfs_scheduler
NAME2 = rr_scheduler
NAME3 = edf_scheduler

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