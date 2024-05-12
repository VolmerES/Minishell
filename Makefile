# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
CLEAR	=	\033[0m

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -g3
SRC = ./src/minishell.c ./src/shlvl.c ./src/expander.c ./src/utils.c ./src/builtins/builtins.c ./src/signal.c ./src/parserone.c ./src/logo.c ./src/overexpander.c \
		./src/builtins/cd.c ./src/tokenizer.c ./src/builtins/pwd.c ./src/builtins/utils.c ./src/builtins/echo.c ./src/builtins/export.c ./src/builtins/export_empty.c \
		./src/builtins/export_manage.c ./src/tokenize_redir.c ./src/builtins/unset.c ./src/builtins/env.c ./src/executor/executor.c ./src/quotes_eraser.c ./src/tokenizer_two.c \
		./src/executor/one_command.c ./src/executor/utils.c ./src/executor/multi_command.c
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
	@rm -rf $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)minishell objects removed!$(CLEAR)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)minishell removed!$(CLEAR)"
	@rm -rf Historial

re: fclean $(NAME)

run: all
	@clear
	@./$(NAME)


# Descomment the line to get leaks
VALGRIND_FLAGS=#--leak-check=full
valgrind: all
	@clear
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)

.PHONY: all clean fclean re