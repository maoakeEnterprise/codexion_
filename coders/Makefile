#============================
# ALL FILES 
#============================

SRC = main.c parsing.c init_struct.c utils.c free.c free_crash.c coders.c coders_util.c \
	  utils_two.c monitor.c dongle.c scheduler.c utils_sheduler.c dongle_utils.c coders_util_two.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

NAME = codexion

OBJ = $(SRC:.c=.o)

DEP = $(OBJ:.o=.d)

.PHONY: all clean fclean re test codex debug norming valgrind valgrind2

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# number_of_coders        time_to_burnout                    time_to_compile    time_to_debug
# time_to_refactor        number_of_compiles_required        dongle_cooldown scheduler
codex:
	./$(NAME) 4 80 200 200 200 5 100 fifo

codex2:
	./$(NAME) 50 190 60 60 60 5 0 edf

clean:
	rm -rf $(OBJ) $(DEP) $(OBJ_TEST) $(DEP_TEST) $(OBJ_TEST_INIT) $(DEP_TEST_INIT)

debug: fclean
	$(MAKE) CFLAGS=" -Wall -Werror -Wextra -pthread -fsanitize=thread -g"

valgrind:
	valgrind --tool=helgrind ./$(NAME) 4 80 200 200 200 5 100 fifo

valgrind2:
	valgrind --tool=drd ./$(NAME) 20 1500 100 200 200 2 10 fifo

norming:
	watch norminette $(SRC) codexion.h

fclean: clean
	rm -f $(NAME) $(NAME_TEST1) $(NAME_TEST2)

re: fclean all

-include $(DEP) $(DEP_TEST) $(DEP_TEST_INIT)