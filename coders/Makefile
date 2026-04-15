#============================
# ALL FILES 
#============================

SRC = main.c parsing.c init_struct.c utils.c free.c free_crash.c coders.c coders_util.c \
	  utils_two.c

TEST = test_parsing.c parsing.c

TEST_INIT = test_init.c parsing.c init_struct.c utils.c free.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

NAME = codexion

NAME_TEST1 = test_parsing

NAME_TEST2 = test_init

OBJ = $(SRC:.c=.o)

OBJ_TEST = $(TEST:.c=.o)

OBJ_TEST_INIT = $(TEST_INIT:.c=.o)

DEP = $(OBJ:.o=.d)

DEP_TEST = $(OBJ_TEST:.o=.d)

DEP_TEST_INIT = $(OBJ_TEST_INIT:.o=.d)

.PHONY: all clean fclean re test test_init codex debug

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

test: $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) -o $(NAME_TEST1)
	./$(NAME_TEST1)

codex:
	./$(NAME) 22 22 22 10 22 22 22 fifo

test_init: $(OBJ_TEST_INIT)
	$(CC) $(CFLAGS) $(OBJ_TEST_INIT) -o $(NAME_TEST2)
	./$(NAME_TEST2)

clean:
	rm -rf $(OBJ) $(DEP) $(OBJ_TEST) $(DEP_TEST) $(OBJ_TEST_INIT) $(DEP_TEST_INIT)

debug: fclean
	$(MAKE) CFLAGS=" -Wall -Werror -Wextra -pthread -fsanitize=thread"

valgrind:
	valgrind --tool=helgrind ./$(NAME) 22 22 22 10 22 22 22 fifo

fclean: clean
	rm -f $(NAME) $(NAME_TEST1) $(NAME_TEST2)

re: fclean all

-include $(DEP) $(DEP_TEST) $(DEP_TEST_INIT)