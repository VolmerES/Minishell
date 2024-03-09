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
}               t_msh;
