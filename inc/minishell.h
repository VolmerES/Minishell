/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                                          :::      ::::::::   */
/*                                     					 :+:      :+:    :+:  */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by david             #+#    #+#             */
/*   Updated: 2024/03/05 22:50:46 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h> //? Necesaria para el manejo de señales
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termcap.h> // Necesaria para tgetstr
# include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define OR1 "\033[38;5;208m"
# define OR2 "\033[38;5;214m"
# define OR3 "\033[38;5;220m"
# define YE1 "\033[38;5;226m"
# define YE2 "\033[38;5;229m"
# define YE3 "\033[38;5;227m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

#define SPACE ' '
#define DOLLAR '$'
#define DQUOTES '\"'
#define SQUOTES '\''
#define BACKSLASH '\\'
#define UNDERSCORE '_'
#define PIPE '|'
#define MAX_COMMANDS 1000
#define PWD './'

typedef enum s_err_msg
{
	PIPE_,
	FORK_,
	MALLOC_
}				t_err_msg;
typedef struct s_parser
{
	int	index;
	int	start;
	int	in_quotes;
	int	cmd_index;
	int	in_single_quotes;
	int k;
}				t_parser;

typedef enum e_file_type
{
	INFILE_NORMAL = 0,
	INFILE_HERE_DOC = 1,
	OUTFILE_TRUNC = 2,
	OUTFILE_APPEND = 3
}	t_file_type;

typedef struct s_file
{
	char		*filename;
	t_file_type	type;
}				t_file;

typedef struct s_cmd
{
	/*Contenido input por pipes*/
	char	*cmd;

	/*Comando principal solo*/
	char	*cmd_main;

	/*Comando con argumentos*/
	char	**full_cmd;

	/*Argumentos del comando*/
	char	**args;


	/*Infile del comando*/
	t_file	**infile;

	/*Outfile del comando*/
	t_file	**outfile;
}				t_cmd;

typedef struct s_msh
{
	/* Input del usuario */
	char		*input;

	/* Comando segmentado */
	t_cmd		**cmds;

	/* Variables entorno */
	char		**envp;

	/* Path */
	char		**path;

	/*Variable entorno expandida*/
	char		*evar;

	int 		special_char;

	t_parser	parser;

	/*Entrada stdin*/
	int			cp_stdin;

	/*Salida stdout*/
	int			cp_stdout;

	/*Entrada anterior*/
	int			cp_stdin_last;

	/*Salida anterior*/
	int			cp_stdout_last;

	/*Ultimo pid*/
	pid_t		last_pid;

	/*Fd pipe*/
	int			pipefd[2];

	/* Salida del ultimo comando */
	int			last_out;
}				t_msh;

typedef struct s_counters
{
	int	i;
	int	j;
	int	k;
	int	l;
}				t_counters;

/*OVEREXPANDER.c*/
void		ft_overwrited_expand(t_msh *commands);
char		*ft_get_env_var_value(t_msh *commands, char *var_name);
char		*ft_get_var_name(char *input, int *i);
void		ft_replace_var_with_value(t_msh *commands, char *var_value, int i,
				int var_len);

/*PROGRAMA MAIN*/
void		ft_manage(t_msh *commands);
void		ft_sigint(int sign);
void		ft_init_struct(t_msh *commands);
void		ft_shlvl(t_msh *commands, char **envp);
void		ft_handle_readline(t_msh *commands);

/*PARSEO COMILLAS*/
int			ft_incomplete_quotes(t_msh *commands);

/*UTILIDADES*/
int			ft_strcmp(const char *str1, const char *str2);
void		free_struct(t_msh *commands);

/*MANAGER SHELL LEVEL*/
int			ft_search_shlvl(char **env);
void		ft_free_matrix(char **env);
void		generation_pwd(t_msh *commands);
char		**ft_manage_shlvl(char **minienv);
char		**ft_copy_envp(char **envp);
char		**ft_addvariable(char **minienv, char *aux);
int			ft_search_env(char **env, char *tofind);

/*EXPANDER DE VARIABLES DE ENTORNO*/
char		*ft_manage_expander(char **envpc, int index, char *evar);
void		ft_expand(t_msh *commands);
int			ft_check_syntax(char *evar, t_msh *commands);
char		*ft_get_var(t_msh *commands, int i);
void		ft_expand_var(t_msh *commands);

/*BUILTINS.c*/
void		ft_builtins(t_msh *commands, int i);

/*SINGAL.c*/
void		ft_signal_handler(void);

/*PARSERONE.c*/
void		ft_parse_input(t_msh *commands);
void		print_commands(t_msh *commands);
void		ft_process_character(t_msh *commands);
void		ft_add_command(t_msh *commands, int *start,
				int *index, int *cmd_index);
void		allocate_commands(t_msh *commands);
int			ft_count_pipes(t_msh *commands);
void		set_null(t_msh *commands, int index);
/*LOGO.c*/
void		ft_logo(void);

/*TOKENIZER.c*/
void		ft_tokenize(t_msh *commands);
void		increment_j(t_msh *commands, int *i, int *j);
void		ft_arguments(t_msh *commands, int *i, int *j);
void		ft_tokenize_command(t_msh *commands, int *i);

/*TOKENIZE REDIR*/
void		ft_is_command(t_msh *commands, int *i, int *j);
void		ft_is_outfile_trunc(t_msh *commands, int *i, int *j);
void		ft_is_outfile_append(t_msh *commands, int *i, int *j);
void		ft_is_infile(t_msh *commands, int *i, int *j);
void		ft_is_infile_here_doc(t_msh *commands, int *i, int *j);

/*BUILTINS/BUILTINS.c*/
int			cd_builtin(t_msh *commands, int i);
int			pwd_builtin(t_msh *commands);
int			echo_builtin(t_msh *commands, int i);
int			check_num_args(t_msh *commands, int i);
int			export_builtin(t_msh *commands, int i);
int			is_builtins(t_msh *commands, int i);
int			open_files(t_msh *commands, int cmd_i, int pipe);
int			out_files(t_msh *commands, int cmd_i, int pipe);
int			unset_builtin(t_msh *commands, int i);
int			env_builtin(t_msh *commands);

void		export_empty(t_msh *commands);
void		manage_export(t_msh *commands, int num_command);
void		update_env(t_msh *commands, int index, char *value);
void    	executor_manage(t_msh *commands);
void    	bd_one_command(t_msh *commands);
void    	one_command(t_msh *commands);
void    	multi_command(t_msh *commands);
void		exit_builtin(t_msh *commands, int cmd_i);

char		*check_path(char **path, char *command);
char		**find_path(char **env);
char 		**add_to_arg(char **path, char *new_path);

/*QUOTES ERASER*/
void ft_trim_end(char *str);
void	ft_erase_cmd_quotes(t_msh *commands, int *i);
void	ft_erase_arg_quotes(t_msh *commands);

/*TOKENIZER_TWO*/
void	ft_handle_less_than(t_msh *commands, int *i, int *j);
void	ft_handle_greater_than(t_msh *commands, int *i, int *j);
void	ft_handle_else(t_msh *commands, int *i, int *j);

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size);

/* EXECUTOR */

void	exit_(t_err_msg error);
void	exit_err(t_msh *commands, int cmd_i);
void	first_child(t_msh *commands, int *fd);
void	mid_child(t_msh *commands, int *fd, int *new, int cmd_i);
void	last_child(t_msh *commands, int *fd);
char	*her_doc(char *name);

void printArray(char *array[]);