/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:26:28 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/06/01 16:34:52 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_pipes(t_msh *commands)
{
	int	i;
	int	count;
	int	in_single_quote;
	int	in_double_quote;

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
