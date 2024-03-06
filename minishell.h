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
