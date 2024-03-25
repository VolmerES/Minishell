#include "../inc/minishell.h"

static void ft_is_commands_and_args(t_msh *commands, int *i)
{
    
}

static void   ft_is_outfile_trunc(t_msh *commands, int *i)
{
    t_file  *outfile;
    int     j;
    char    *filename;

    outfile = malloc(sizeof(t_file));
    filename = "";
    j = 0;
    if (commands->cmds[*i]->cmd[j] == '>')
        j++;
    while (commands->cmds[*i]->cmd[j] == ' ')
        j++;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ' 
    && commands->cmds[*i]->cmd[j] != '>')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, 0, j);
    outfile->filename = filename;
    outfile->type = OUTFILE_TRUNC;
    commands->cmds[*i]->outfile = outfile;
}

static void    ft_is_outfile_append(t_msh *commands, int *i)
{
    t_file  *outfile;
    int     j;
    char    *filename;

    outfile = malloc(sizeof(t_file));
    filename = "";
    j = 0;
    if (commands->cmds[*i]->cmd[j] == '>')
        j++;
    if (commands->cmds[*i]->cmd[j] == '>')
        j++;
    while (commands->cmds[*i]->cmd[j] == ' ')
        j++;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ' 
    && commands->cmds[*i]->cmd[j] != '>')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, 0, j);
    outfile->filename = filename;
    outfile->type = OUTFILE_APPEND;
    commands->cmds[*i]->outfile = outfile;
}

static void    ft_is_infile(t_msh *commands, int *i)
{
    t_file  *infile;
    int     j;
    char    *filename;

    infile = malloc(sizeof(t_file));
    filename = "";
    j = 0;
    if (commands->cmds[*i]->cmd[j] == '<')
        j++;
    while (commands->cmds[*i]->cmd[j] == ' ')
        j++;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ' 
    && commands->cmds[*i]->cmd[j] != '<')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, 0, j);
    infile->filename = filename;
    infile->type = INFILE_NORMAL;
    commands->cmds[*i]->infile = infile;
}

static void    ft_is_infile_here_doc(t_msh *commands, int *i)
{
    t_file  *infile;
    int     j;
    char    *filename;

    infile = malloc(sizeof(t_file));
    filename = "";
    j = 2;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, 2, j - 2);
    infile->filename = filename;
    infile->type = INFILE_HERE_DOC;
    commands->cmds[*i]->infile = infile;
}

static void    ft_tokenize_command(t_msh *commands, int index)
{
    int *i;
    int skip;
    int j;

    j = 0;
    *i = index;
    while(commands->cmds[*i]->cmd[j] != '\0')
    {
        if (commands->cmds[*i]->cmd[j] == '<')
        {
            if (commands->cmds[*i]->cmd[j + 1] == '<')
                ft_is_infile_here_doc(commands, i); // <<: here_doc
            else 
                ft_is_infile(commands, i); // <: Infile normal
        }
        else if (commands->cmds[*i]->cmd[j] == '>')
        {
            if (commands->cmds[*i]->cmd[j + 1] == '>')
                ft_is_outfile_append(commands, i); // >>: Append
            else
                ft_is_outfile_trunc(commands, i); // >: TRUNC
        }
        //condicion para los segmentar los comandos y argumentos
        else
        {
            ft_is_commands_and_args(commands, i);
        }
        j++;
    }
}
void		ft_tokenize(t_msh *commands)
{
    int i;

    i = 0;
    while (commands->cmds[i] != NULL)
    {
        ft_tokenize_command(commands, i);
        i++;
    }
}
