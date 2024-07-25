#include "../inc/minishell.h"

int ft_count_pipes(t_msh *commands)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (commands->input[i])
	{
		if(commands->input[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}
