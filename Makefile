# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
CLEAR	=	\033[0m

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra  
SRC = ./src/minishell.c ./src/shlvl.c ./src/expander.c ./src/utils.c ./src/builtins.c ./src/signal.c ./src/parserone.c ./src/logo.c ./src/overexpander.c
OBJ = $(SRC:.c=.o)
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW)Compiling minishell...$(CLEAR)"
	@$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) -lreadline -ltermcap $(LIBFT)
	@echo "$(GREEN)minishell compiled!$(CLEAR)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(CLEAR)"
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compiled!$(CLEAR)"

clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)minishell objects removed!$(CLEAR)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)minishell removed!$(CLEAR)"
	@rm Historial

re: fclean $(NAME)

run: all
	clear
	./$(NAME)

.PHONY: all clean fclean re