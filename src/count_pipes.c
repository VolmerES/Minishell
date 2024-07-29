#include "../inc/minishell.h"

int ft_count_pipes(t_msh *commands)
{
    int i;
    int count;
    int in_single_quote;
    int in_double_quote;

    i = 0;
    count = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    while (commands->input[i])
    {
        if (commands->input[i] == SQUOTES && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (commands->input[i] == DQUOTES && !in_single_quote)
            in_double_quote = !in_double_quote;
        if (commands->input[i] == PIPE && !in_single_quote && !in_double_quote)
            count++;
        i++;
    }
    return (count + 1);
}
