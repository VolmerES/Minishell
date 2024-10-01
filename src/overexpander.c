/* ************************************************************************** */
/*                                                                            */
/*   overexpander.c                                       :::      ::::::::   */
/*                                     		       		:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/04/15 13:02:49 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_env_var_value(t_msh *commands, char *var_name)
{
	char	*var_value;
	char	**value;
	int		index;

	index = ft_search_env(commands->envp, var_name);
	if (index != -1)
	{
		value = ft_split(commands->envp[index], '=');
		var_value = ft_strdup(value[1]);
		ft_free_matrix(value);
	}
	else
		var_value = ft_strdup("");
	return (var_value);
}

char	*ft_get_var_name(char *input, int *i)
{
	int	var_len;

	var_len = 1;
	while (input[*i + var_len] != SPACE && input[*i + var_len] != '\0'
		&& input[*i + var_len] != DOLLAR && input[*i + var_len] != DQUOTES
		&& input[*i + var_len] != SQUOTES)
		var_len++;
	return (ft_substr(input, *i + 1, var_len - 1));
}

void	ft_replace_var_with_value(t_msh *commands, char *var_value, int i,
		int var_len)
{
	char	*before;
	char	*after;
	char	*temp;

	before = ft_substr(commands->input, 0, i);
	after = ft_substr(commands->input, i + var_len, ft_strlen(commands->input)
			- (i + var_len));
	temp = ft_strjoin(before, var_value);
	free(commands->input);
	commands->input = ft_strjoin(temp, after);
	free(temp);
	free(before);
	free(after);
}

void	ft_overwrited_expand(t_msh *commands)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while (commands->input[i] != '\0')
	{
		if (commands->input[i] == DOLLAR && commands->input[i + 1] != '\0')
		{
			var_name = ft_get_var_name(commands->input, &i);
			var_value = ft_get_env_var_value(commands, var_name);
			ft_replace_var_with_value(commands, var_value, i,
				ft_strlen(var_name) + 1);
			i += ft_strlen(var_value) - 1;
			free(var_name);
			free(var_value);
		}
		i++;
	}
}
