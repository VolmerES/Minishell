/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/19 18:19:42 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int		g_signal_control;

void	ft_construct_new_input(t_msh *commands, char *expvar, char *pos)
{
	char	*result;
	size_t	initial_len;
	size_t	expanded_len;
	size_t	final_len;

	initial_len = pos - commands->input;
	expanded_len = ft_strlen(expvar);
	final_len = ft_strlen(commands->input) - 2 + expanded_len + 1;
	result = malloc(final_len);
	if (result == NULL)
	{
		printf("Error: Memory allocation failed. Unable to continue.\n");
		free(expvar);
		exit(1);
	}
	ft_strncpy(result, commands->input, initial_len, final_len);
	ft_strlcat(result, expvar, final_len);
	ft_strlcat(result, pos + 2, final_len);
	free(commands->input);
	commands->input = result;
	if (commands->input == NULL)
		free(expvar);
}

void	ft_expand_special(t_msh *commands)
{
	char	*expanded_variable;
	char	*pos;

	if (g_signal_control == 130)
		commands->last_out = g_signal_control;
	expanded_variable = ft_itoa(commands->last_out);
	if (expanded_variable == NULL)
	{
		printf("Error: Memory allocation failed. Unable to continue.\n");
		exit(1);
	}
	pos = ft_strstr(commands->input, "$?");
	if (pos == NULL)
	{
		free(expanded_variable);
		return ;
	}
	ft_construct_new_input(commands, expanded_variable, pos);
	free(expanded_variable);
}

char	*ft_manage_expander(char **envpc, int index, char *evar)
{
	const char	*equal_sign;
	char		*expanded_variable;

	if (index < 0)
		return (NULL);
	free(evar);
	if (index >= 0)
	{
		equal_sign = ft_strchr(envpc[index], '=');
		if (equal_sign != NULL)
		{
			expanded_variable = ft_strdup(equal_sign + 1);
			if (expanded_variable == NULL)
			{
				printf("Error: Memory allocation failed.\n");
				free(expanded_variable);
				exit(1);
			}
			return (expanded_variable);
		}
	}
	return (NULL);
}

void	ft_expand(t_msh *commands)
{
	int	i;

	i = ft_search_env(commands->envp, commands->evar);
	if (i == -1)
		free(commands->evar);
	commands->evar = ft_manage_expander(commands->envp, i, commands->evar);
	if (commands->evar == NULL)
		free(commands->evar);
}

int	ft_check_syntax(char *evar, t_msh *commands)
{
	int	i;

	i = 0;
	while (evar[i] != '\0')
	{
		if (ft_isdigit(evar[0]) == 1 || evar[0] == '=')
		{
			printf("error: not a valid identifier\n");
			commands->last_out = 1;
			return (1);
		}
		if (ft_isalpha(evar[i]) == 0 && evar[i] != UNDERSCORE
			&& ft_isdigit(evar[i + 1]) != 0)
		{
			printf("error: not a valid identifier\n");
			commands->last_out = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
