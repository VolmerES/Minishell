/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:30:47 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/07 19:38:08 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_quotes_flag_expander(char *str, int i)
{
	static int	flag;

	flag = 0;
	if (str[i] == SQUOTES && (i == 0 || str[i - 1] != BACKSLASH))
	{
		if (flag == 1)
			flag = 0;
		else if (flag == 0)
			flag = 1;
	}
	else if (str[i] == DQUOTES && (i == 0 || str[i - 1] != BACKSLASH))
	{
		if (flag == 2)
			flag = 0;
		else if (flag == 0)
			flag = 2;
	}
	return (flag);
}

void	ft_handle_quotes(t_msh *commands, int *i, int *flag)
{
	int	j;

	if ((commands->input[*i] == SQUOTES
			|| commands->input[*i] == DQUOTES)
		&& (*i == 0 || commands->input[*i - 1] != BACKSLASH))
	{
		*flag = ft_quotes_flag_expander(commands->input, *i);
	}
	if (*i > 0 && commands->input[*i] == DOLLAR
		&& commands->input[*i - 1] == DQUOTES
		&& commands->input[*i + 1] != SPACE
		&& commands->input[*i + 1] != '\0'
		&& commands->input[*i - 2] == SQUOTES)
	{
		j = *i + 1;
		while (commands->input[j] && !(commands->input[j] == DQUOTES
				&& commands->input[j + 1] == SQUOTES))
			j++;
	}
}

void	ft_expand_variables(t_msh *commands, int i, int flag)
{
	if (commands->input[i] == DOLLAR
		&& commands->input[i + 1] != SPACE
		&& commands->input[i + 1] != '\0'
		&& (flag != 1))
	{
		if (commands->input[i] == DOLLAR && commands->input[i + 1] == '?')
			ft_expand_special(commands);
		else if (commands->input[i] == DOLLAR)
		{
			commands->evar = ft_get_var(commands, i + 1);
			if (!commands->evar)
			{
				exit(1);
			}
			printf("\033[34mVariable de entorno sin expandir: %s\033[0m\n",
				commands->evar);
			ft_expand(commands);
			ft_overwrited_expand(commands);
			printf("\033[34mVariable de entorno expandida: %s\033[0m\n",
				commands->evar);
		}
	}
}

void	ft_expand_var(t_msh *commands)
{
	int	i;
	int	flag;

	i = 0;
	while (commands->input[i] != '\0')
	{
		ft_handle_quotes(commands, &i, &flag);
		ft_expand_variables(commands, i, flag);
		i++;
	}
}

char	*ft_get_var(t_msh *commands, int i)
{
	size_t	len;
	char	*evar;

	len = 0;
	while (commands->input[i] != SPACE && commands->input[i] != '\0'
		&& commands->input[i] != DQUOTES && commands->input[i] != SQUOTES)
	{
		i++;
		len++;
	}
	evar = malloc(len + 1);
	if (!evar)
	{
		printf("Error: Memory allocation failed. Unable to continue.\n");
		exit(EXIT_FAILURE);
	}
	strncpy(evar, &commands->input[i - len], len);
	evar[len] = '\0';
	ft_check_syntax(evar, commands);
	return (evar);
}
