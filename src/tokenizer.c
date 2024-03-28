#include "../inc/minishell.h"

static void ft_is_commands_and_args(t_msh *commands, int *i)
{
    
}

static void   ft_is_outfile_trunc(t_msh *commands, int *i)
{
    t_file  *outfile;
    int     j;
    char    *filename;
    int     start;

    outfile = malloc(sizeof(t_file));
    filename = "";
    j = 0;
    while (commands->cmds[*i]->cmd[j] != '>' && commands->cmds[*i]->cmd[j] != '\0')
        j++;
    if (commands->cmds[*i]->cmd[j] == '>')
        j++;
    while (commands->cmds[*i]->cmd[j] == ' ')
        j++;
    start = j;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, start, j - start);
    outfile->filename = filename;
    outfile->type = OUTFILE_TRUNC;
    commands->cmds[*i]->outfile = outfile;
    printf("Trunc: %s\n", outfile->filename);
}

static void    ft_is_outfile_append(t_msh *commands, int *i)
{
    t_file  *outfile;
    int     j;
    char    *filename;
    int     start;

    outfile = malloc(sizeof(t_file));
    filename = "";
    j = 0;
    while (commands->cmds[*i]->cmd[j] != '\0') 
    {
        if (commands->cmds[*i]->cmd[j] == '>' && commands->cmds[*i]->cmd[j + 1] == '>')
            break;
        j++;
    }
    if (commands->cmds[*i]->cmd[j] == '>' && commands->cmds[*i]->cmd[j + 1] == '>')
        j += 2;
    while (commands->cmds[*i]->cmd[j] == ' ')
        j++;
    start = j;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ' 
    && commands->cmds[*i]->cmd[j] != '>')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, start, j - start);
    outfile->filename = filename;
    outfile->type = OUTFILE_APPEND;
    commands->cmds[*i]->outfile = outfile;
    printf("Append: %s\n", outfile->filename);
}

static void    ft_is_infile(t_msh *commands, int *i)
{
    t_file  *infile;
    int     j;
    char    *filename;
    int     start;

    infile = malloc(sizeof(t_file));
    filename = "";
    j = 0;
    while (commands->cmds[*i]->cmd[j] != '<' && commands->cmds[*i]->cmd[j] != '\0')
        j++;
    if (commands->cmds[*i]->cmd[j] == '<')
        j++;
    while (commands->cmds[*i]->cmd[j] == ' ')
        j++;
    start = j;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ' 
    && commands->cmds[*i]->cmd[j] != '<')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, start, j - start);
    infile->filename = filename;
    infile->type = INFILE_NORMAL;
    commands->cmds[*i]->infile = infile;
    printf("Infile: %s\n", infile->filename);
}

static void    ft_is_infile_here_doc(t_msh *commands, int *i)
{
    t_file  *infile;
    int     j;
    char    *filename;
    int     start;

    infile = malloc(sizeof(t_file));
    filename = "";
    j = 0;
    while (commands->cmds[*i]->cmd[j] != '\0') 
    {
        if (commands->cmds[*i]->cmd[j] == '<' && commands->cmds[*i]->cmd[j + 1] == '<')
            break;
        j++;
    }
    if (commands->cmds[*i]->cmd[j] == '<' && commands->cmds[*i]->cmd[j + 1] == '<')
        j += 2;
    while (commands->cmds[*i]->cmd[j] == ' ')
        j++;
    start = j;
    while (commands->cmds[*i]->cmd[j] != '\0' && commands->cmds[*i]->cmd[j] != ' ' 
    && commands->cmds[*i]->cmd[j] != '<')
    {
        j++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, start, j - start);
    infile->filename = filename;
    infile->type = INFILE_HERE_DOC;
    commands->cmds[*i]->infile = infile;
    printf("Here_doc: %s\n", infile->filename);
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
            {
                ft_is_infile_here_doc(commands, i); // <<: here_doc
                j++; // Skip the next '<'
            }
            else 
                ft_is_infile(commands, i); // <: Infile normal
        }
        else if (commands->cmds[*i]->cmd[j] == '>')
        {
            if (commands->cmds[*i]->cmd[j + 1] == '>')
            {
                ft_is_outfile_append(commands, i); // >>: Append
                j++; // Skip the next '>'
            }
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
