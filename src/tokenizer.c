#include "../inc/minishell.h"

void    ft_is_infilet_here_doc(t_cmd *current, int *i)
{
    t_file  *infile;
    int     j;
    char    *filename;

    infile = malloc(sizeof(t_file));
    j = 0;
    *i += 2;
    while (current->cmds[*i][j] != '\0')
    {
        filename = ft_strjoin(filename, current->cmds[*i][j]);
        j++;
    }
    infile->filename = filename;
    infile->type = INFILE_HERE_DOC;
    commands->cmds[*i]->infile = infile;
}

void    ft_tokenize_command(t_msh *commands, int index)
{
    int *i;
    int skip;
    t_msh   *current;

    i = 0;
    current = commands->cmds[index];
    while(current->cmds[*i] != '\0')
    {
        skip = 0;
        if (current->cmds[*i] == '<')
        {
            if (current->cmds[*i + 1] == '<') 
                ft_is_infilet_here_doc(current, i); // <<: here_doc
            else 
                ft_is_infile(current, i); // <: Infile normal
                
        }
        else if (current->cmds[*i] == '>')
        {
            if (current->cmds[*i + 1] == '>')
                ft_is_outfile_append(current, i); // >>: Append
            else
                ft_is_outfile_trunc(current, i); // >: TRUNC
        }
        else
        {
            ft_is_commands_and_args(current);
        }
        *i++;
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
