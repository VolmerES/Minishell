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
#include "Libft/libft.h"
#include <termcap.h>  // Necesaria para tgetstr

typedef struct  s_cmd{

    /*Comando principal*/
    char    *cmd;

    /*Argumentos del comando*/
    char    **args;

    /*Infile del comando*/
    char    **infile;

    /*Outfile del comando*/
    char    **outfile;

    /*Tipo de comando*/
    char    *filetype;


}               t_cmd;


typedef struct  s_msh{

    /*Input del usuario*/
    char *input;

    /*Comando segmentado*/
    t_cmd **cmd;

    /*Variables entorno*/
    char    **envp;
}               t_msh;

void    ft_manage(t_msh *commands);
void    ft_sigint(int sign);

int ft_incomplete_squotes(t_msh *commands);
int ft_incomplete_dquotes(t_msh *commands);


int	ft_strcmp(const char *str1, const char *str2);

int ft_search_shlvl(char **env);
void    ft_free_matrix(char **env);
char    **ft_manage_shlvl(char **minienv);
char    **ft_copy_envp(char **envp);
char **ft_addVariable(char **minienv, char *aux);