NAME  = philo

SRC_DIR = src

SRC =	main.c			\
		utils.c			\
		thread.c		\
		status.c		\
		handle_fork.c	\
		print.c			\
		dead.c			\
		getters.c

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I./include
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re