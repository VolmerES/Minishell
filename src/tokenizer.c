#include "../inc/minishell.h"

static void ft_arguments(t_msh *commands, int *i, int *j)
{
    while (commands->cmds[*i]->cmd[*j] == SPACE)
    {
        (*j)++;
    }
    while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != SPACE && commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '>')
    {
        if (commands->cmds[*i]->cmd[*j] == SPACE)
        {
            (*j)++;
        }
        else
        {
            int start;
            int k;

            k = 0;
            start = *j;
            while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != SPACE && commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '>')
            {
                (*j)++;
            }
            commands->cmds[*i]->args = malloc(sizeof(t_cmd()));
            commands->cmds[*i]->args[k] = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
            printf("Argumento: %s\n", commands->cmds[*i]->args[k]);
            k++;
        }
    }
    commands->cmds[*i]->args = NULL;
}
static void ft_is_command(t_msh *commands, int *i, int *j)
{
    int start;

    start = *j;
    while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ' && commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '>')
    {
        (*j)++;
    }
    commands->cmds[*i]->cmd_main = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
    printf("Comando main: %s\n", commands->cmds[*i]->cmd_main);
    while (commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '>' && commands->cmds[*i]->cmd[*j] != '\0')
    {
        ft_arguments(commands, i, j);
        *j += 1;
    }
}

static void   ft_is_outfile_trunc(t_msh *commands, int *i, int *j)
{
    t_file  *outfile;
    char    *filename;
    int     start;

    outfile = malloc(sizeof(t_file));
    filename = "";
    while (commands->cmds[*i]->cmd[*j] != '>' && commands->cmds[*i]->cmd[*j] != '\0')
        (*j)++;
    if (commands->cmds[*i]->cmd[*j] == '>')
        (*j)++;
    while (commands->cmds[*i]->cmd[*j] == ' ')
        (*j)++;
    start = *j;
    while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ')
        (*j)++;
    filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
    outfile->filename = filename;
    outfile->type = OUTFILE_TRUNC;
    commands->cmds[*i]->outfile = outfile;
    printf("Trunc: %s\n", outfile->filename);
}

static void    ft_is_outfile_append(t_msh *commands, int *i, int *j)
{
    t_file  *outfile;
    char    *filename;
    int     start;

    outfile = malloc(sizeof(t_file));
    filename = "";
    while (commands->cmds[*i]->cmd[*j] != '\0') 
    {
        if (commands->cmds[*i]->cmd[*j] == '>' && commands->cmds[*i]->cmd[*j + 1] == '>')
            break;
        (*j)++;
    }
    if (commands->cmds[*i]->cmd[*j] == '>' && commands->cmds[*i]->cmd[*j + 1] == '>')
        (*j) += 2;
    while (commands->cmds[*i]->cmd[*j] == ' ')
        (*j)++;
    start = *j;
    while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ' 
    && commands->cmds[*i]->cmd[*j] != '>')
    {
        (*j)++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
    outfile->filename = filename;
    outfile->type = OUTFILE_APPEND;
    commands->cmds[*i]->outfile = outfile;
    printf("Append: %s\n", outfile->filename);
}

static void    ft_is_infile(t_msh *commands, int *i, int  *j)
{
    t_file  *infile;
    char    *filename;
    int     start;

    infile = malloc(sizeof(t_file));
    filename = "";
    while (commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '\0')
        (*j)++;
    if (commands->cmds[*i]->cmd[*j] == '<')
        (*j)++;
    while (commands->cmds[*i]->cmd[*j] == ' ')
        (*j)++;
    start = *j;
    while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ' 
    && commands->cmds[*i]->cmd[*j] != '<')
    {
        (*j)++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
    infile->filename = filename;
    infile->type = INFILE_NORMAL;
    commands->cmds[*i]->infile = infile;
    printf("Infile: %s\n", infile->filename);
}

static void    ft_is_infile_here_doc(t_msh *commands, int *i, int *j)
{
    t_file  *infile;
    char    *filename;
    int     start;

    infile = malloc(sizeof(t_file));
    filename = "";
    while (commands->cmds[*i]->cmd[*j] != '\0') 
    {
        if (commands->cmds[*i]->cmd[*j] == '<' && commands->cmds[*i]->cmd[*j + 1] == '<')
            break;
        (*j)++;
    }
    if (commands->cmds[*i]->cmd[*j] == '<' && commands->cmds[*i]->cmd[*j + 1] == '<')
        (*j) += 2;
    while (commands->cmds[*i]->cmd[*j] == ' ')
        (*j)++;
    start = *j;
    while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ' 
    && commands->cmds[*i]->cmd[*j] != '<')
    {
        (*j)++;
    }
    filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
    infile->filename = filename;
    infile->type = INFILE_HERE_DOC;
    commands->cmds[*i]->infile = infile;
    printf("Here_doc: %s\n", infile->filename);
}

static void    ft_tokenize_command(t_msh *commands, int *i)
{
    int j;

    j = 0;
    while(commands->cmds[*i]->cmd[j] != '\0')
    {
        if (commands->cmds[*i]->cmd[j] == '<')
        {
            if (commands->cmds[*i]->cmd[j + 1] == '<')
            {
                ft_is_infile_here_doc(commands, i, &j); // <<: here_doc
            }
            else 
                ft_is_infile(commands, i, &j); // <: Infile normal
        }
        else if (commands->cmds[*i]->cmd[j] == '>')
        {
            if (commands->cmds[*i]->cmd[j + 1] == '>')
            {
                ft_is_outfile_append(commands, i, &j); // >>: Append
                j++; // Skip the next '>'
            }
            else
                ft_is_outfile_trunc(commands, i, &j); // >: TRUNC
        }
        //condicion para los segmentar los comandos y argumentos
        else
        {
            ft_is_command(commands, i, &j);
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
        ft_tokenize_command(commands, &i);
        i++;
    }
}
