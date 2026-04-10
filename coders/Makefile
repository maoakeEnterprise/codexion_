#============================
# ALL FILES 
#============================

SRC = main.c parsing.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

NAME = codexion

OBJ = $(SRC:.c=.o)

DEP = $(OBJ:.o=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)⏎  