/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:30:47 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/19 23:01:37 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_quotes_flag_expander(char *str, int i)
{
	static int	flag;

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
		&& commands->input[*i - 2] != SQUOTES)
	{
		j = *i + 1;
		while (commands->input[j] && !(commands->input[j] == DQUOTES
				&& commands->input[j + 1] == SQUOTES))
			j++;
	}
}

void	ft_expand_variables(t_msh *commands, int i, int flag)
{
	if (i + 1 >= (int)ft_strlen(commands->input))
		return ;
	if (commands->input[i] == DOLLAR
		&& commands->input[i + 1] != SPACE
		&& commands->input[i + 1] != '\0'
		&& (flag != 1))
	{
		if (commands->input[i] == DOLLAR && commands->input[i + 1] == '?')
			ft_expand_special(commands);
		else if (commands->input[i] == DOLLAR)
		{
			if (ft_isdigit(commands->input[i + 1]) == 1)
				return (ft_erase_first_number(commands, i));
			commands->evar = ft_get_var(commands, i + 1);
			if (commands->evar == NULL)
			{
				exit (1);
			}
			ft_expand(commands);
			ft_overwrited_expand(commands, i);
			free(commands->evar);
			commands->evar = NULL;
		}
	}
}

void	ft_expand_var(t_msh *commands)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (commands->input[i] != '\0')
	{
		ft_handle_quotes(commands, &i, &flag);
		if (commands->input[i] == '\0')
			return ;
		ft_expand_variables(commands, i, flag);
		if (commands->input[i] == '\0')
			return ;
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
	evar = ft_calloc(len + 1, sizeof(char));
	if (!evar)
	{
		printf("Error: Memory allocation failed. Unable to continue.\n");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(evar, &commands->input[i - len], len, len);
	evar[len] = '\0';
	if (ft_check_syntax(evar, commands) == 1)
	{
		free(evar);
		return (NULL);
	}
	return (evar);
}
