/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                                          :::      ::::::::   */
/*                                     					 :+:      :+:    :+:   */
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

#define SPACE ' '
#define DOLLAR '$'
#define DQUOTES '\"'
#define SQUOTES '\''
#define BACKSLASH '\\'
#define UNDERSCORE '_'
#define PIPE '|'
#define MAX_COMMANDS 1000

typedef enum  e_file_type {
	INFILE_NORMAL = 0,
	INFILE_HERE_DOC,
	OUTFILE_TRUNC,
	OUTFILE_APPEND
} t_file_type;

typedef struct s_file
{
	char	*filename;

	t_file_type	type;

	//int type; // 0 in_normal, 1 in_here_doc, 2 out_truc, 3 out_append

} t_file;

typedef struct s_cmd
{
	/*Comando principal*/
	char	*cmd;

	/*Argumentos del comando*/
	char	**args;

	/*Infile del comando*/
	t_file	*infile;

	// ls >1 <9 >2 >>3
	//Infiles:	[{"1", INFILE_NORMAL}, {"2", INFILE_NORMAL}, {"3", INFILE_HERE_DOC}]
	//Outfiles:	[{"9", OUTFILE_TRUC}]

	/*Outfile del comando*/
	t_file	*outfile;
}			t_cmd;

typedef struct s_msh
{
	/* Input del usuario */
	char	*input;

	/* Comando segmentado */
	t_cmd	**cmds;

	/* Variables entorno */
	char	**envp;

	/*Variable entorno expandida*/
	char	*evar;
}			t_msh;

/*OVEREXPANDER.c*/
void		ft_overwrited_expand(t_msh *commands);
char		*ft_get_env_var_value(const char *var_name);
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

/*MANAGER SHELL LEVEL*/
int			ft_search_shlvl(char **env);
void		ft_free_matrix(char **env);
char		**ft_manage_shlvl(char **minienv);
char		**ft_copy_envp(char **envp);
char		**ft_addvariable(char **minienv, char *aux);
int			ft_search_env(char **env, char *tofind);

/*EXPANDER DE VARIABLES DE ENTORNO*/
char		*ft_manage_expander(char **envpc, int index, char *evar);
void		ft_expand(t_msh *commands);
int			ft_check_syntax(char *evar);
char		*ft_get_var(t_msh *commands, int i);
void		ft_expand_var(t_msh *commands);

/*BUILTINS.c*/
void		ft_builtins(t_msh *commands);

/*SINGAL.c*/
void		ft_signal_handler(void);

/*PARSERONE.c*/
void		ft_parse_input(t_msh *commands);
void		print_commands(t_msh *commands);
void		process_character(t_msh *commands, int *index, int *start,
				int *in_quotes, int *cmd_index, int *in_single_quotes);
void	ft_add_command(t_msh *commands, int *start, int *index, int *cmd_index);
void		allocate_commands(t_msh *commands);

/*LOGO.c*/
void		ft_logo(void);

/*TOKENIZER.c*/
void		ft_tokenize(t_msh *commands);