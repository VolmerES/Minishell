/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                                          :::      ::::::::   */
/*                                     				    :+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by david             #+#    #+#             */
/*   Updated: 2024/03/05 22:50:46 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Libft/libft.h"
#include <termcap.h>  // Necesaria para tgetstr
#include <signal.h> //? Necesaria para el manejo de señales

#define SPACE ' '
#define DOLLAR '$'
#define DQUOTES '\"'
#define SQUOTES '\''
#define BACKSLASH '\\'
#define UNDERSCORE '_'
#define PIPE '|'
#define MAX_COMMANDS 100

typedef struct  s_cmd{

    /*Comando principal*/
    char    *cmd;

    /*Argumentos del comando*/
    char    *args;

    /*Infile del comando*/
    char    *infile;

    /*Outfile del comando*/
    char    *outfile;

    /*Tipo de comando*/
    char    *filetype;

}               t_cmd;


typedef struct  s_msh{

    /* Input del usuario */
    char *input;

    /* Comando segmentado */
    t_cmd **cmds;

    /* Variables entorno */
    char    **envp;

    /*Variable entorno expandida*/
    char    *evar;
}               t_msh;

            /*PROGRAMA MAIN*/
void    ft_manage(t_msh *commands);
void    ft_sigint(int sign);
void    ft_init_struct(t_msh *commands);
void    ft_shlvl(t_msh *commands, char **envp);
void    ft_handle_readline(t_msh *commands);

            /*PARSEO COMILLAS*/
int     ft_incomplete_quotes(t_msh *commands);

                /*UTILIDADES*/
int     ft_strcmp(const char *str1, const char *str2);

                /*MANAGER SHELL LEVEL*/
int     ft_search_shlvl(char **env);
void    ft_free_matrix(char **env);
char    **ft_manage_shlvl(char **minienv);
char    **ft_copy_envp(char **envp);
char    **ft_addVariable(char **minienv, char *aux);
int     ft_search_env(char **env, char *tofind);

            /*EXPANDER DE VARIABLES DE ENTORNO*/
char    *ft_manage_expander(char **envpc, int index, char *evar);
void    ft_expand(t_msh *commands);
int     ft_check_syntax(char *evar);
char    *ft_get_var(t_msh *commands, int i);
void    ft_expand_var(t_msh *commands);

            /*BUILTINS.c*/
void    ft_builtins(t_msh *commands);
            
            /*SINGAL.c*/
void    ft_signal_handler();

            /*PARSERONE.c*/
void    ft_parse_input(t_msh *commands);
void    print_commands(t_msh *commands);
void process_character(t_msh *commands, int *index, int *start, int *in_quotes, int *cmd_index,  int *in_single_quotes);
void    add_command(t_msh *commands, int *start, int *index, int *cmd_index);
void    allocate_commands(t_msh *commands);

void    ft_logo();