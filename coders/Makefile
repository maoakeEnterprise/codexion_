#============================
# ALL FILES 
#============================

SRC = main.c parsing.c init_struct.c utils.c free.c free_crash.c coders.c coders_util.c \
	  utils_two.c monitor.c dongle.c scheduler.c utils_sheduler.c dongle_utils.c coders_util_two.c

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

.PHONY: all clean fclean re test test_init codex debug norming valgrind valgrind2

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

test: $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) -o $(NAME_TEST1)
	./$(NAME_TEST1)

# number_of_coders        time_to_burnout                    time_to_compile    time_to_debug
# time_to_refactor        number_of_compiles_required        dongle_cooldown scheduler
codex:
	./$(NAME) 1 1500 200 200 200 5 100 edf

test_init: $(OBJ_TEST_INIT)
	$(CC) $(CFLAGS) $(OBJ_TEST_INIT) -o $(NAME_TEST2)
	./$(NAME_TEST2)

clean:
	rm -rf $(OBJ) $(DEP) $(OBJ_TEST) $(DEP_TEST) $(OBJ_TEST_INIT) $(DEP_TEST_INIT)

debug: fclean
	$(MAKE) CFLAGS=" -Wall -Werror -Wextra -pthread -fsanitize=thread -g"

valgrind:
	valgrind --tool=helgrind ./$(NAME) 200 150 100 200 200 5 10 fifo

valgrind2:
	valgrind --tool=drd ./$(NAME) 200 150 100 200 200 2 10 fifo

norming:
	watch norminette $(SRC) codexion.h

fclean: clean
	rm -f $(NAME) $(NAME_TEST1) $(NAME_TEST2)

re: fclean all

-include $(DEP) $(DEP_TEST) $(DEP_TEST_INIT)