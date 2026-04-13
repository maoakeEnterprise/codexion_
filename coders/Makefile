#============================
# ALL FILES 
#============================

SRC = main.c parsing.c init_struct.c utils.c

TEST = test_parsing.c parsing.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

NAME = codexion

NAME_TEST1 = test_parsing

OBJ = $(SRC:.c=.o)

OBJ_TEST = $(TEST:.c=.o)

DEP = $(OBJ:.o=.d)

DEP_TEST = $(OBJ_TEST:.o=.d)

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

test: $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) -o $(NAME_TEST1)
	./$(NAME_TEST1)

clean:
	rm -rf $(OBJ) $(DEP) $(OBJ_TEST) $(DEP_TEST)

fclean: clean
	rm -f $(NAME) $(NAME_TEST1)

re: fclean all

-include $(DEP) $(DEP_TEST)