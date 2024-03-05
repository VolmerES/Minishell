NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra  
SRC = minishell.c
OBJ = $(SRC:.c=.o)
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) -lreadline -ltermcap $(LIBFT)

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean $(NAME)

.PHONY: all clean fclean re