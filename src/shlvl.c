/* ************************************************************************** */
/*                                                                            */
/*   shlvl.c                                              :::      ::::::::   */
/*                                     					:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/03/05 22:50:46 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_addvariable(char **minienv, char *aux)
{
	char	**matrix;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (minienv[i])
		i++;
	matrix = (char **)malloc((i + 2) * sizeof(char *));
	while (j < i)
	{
		matrix[j] = minienv[j];
		j++;
	}
	matrix[i++] = aux;
	matrix[i] = NULL;
	free(minienv);
	return (matrix);
}

int	ft_search_env(char **env, char *tofind)
{
	int		i;
	char	**spl;

	i = 0;
	while (env[i])
	{
		spl = ft_split(env[i], '=');
		if (ft_strcmp(spl[0], tofind) == 0)
			return (ft_free_matrix(spl), i);
		i++;
	}
	return (-1);
}

char	**ft_manage_shlvl(char **minienv)
{
	int		index;
	int		nb;
	char	*nbr;
	char	*aux;

	index = ft_search_env(minienv, "SHLVL");
	if (index == -1)
	{
		aux = ft_strdup("SHLVL=1");
		minienv = ft_addvariable(minienv, aux);
	}
	if (index <= 0)
	{
		nb = ft_atoi(&minienv[index][5]);
		nb += 1;
		nbr = ft_itoa(nb);
		free(minienv[index]);
		minienv[index] = ft_strjoin("SHLVL=", nbr);
		free(nbr);
	}
	return (minienv);
}

char	**ft_copy_envp(char **envp)
{
	char	**minienv;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	minienv = (char **)malloc((count + 1) * sizeof(char *));
	if (!minienv)
		return (ft_free_matrix(minienv), NULL);
	while (envp[i])
	{
		minienv[i] = ft_strdup(envp[i]);
		i++;
	}
	minienv[i] = NULL;
	return (minienv);
}

void	ft_shlvl(t_msh *commands, char **envp)
{
	commands->envp = ft_copy_envp(envp);
	commands->envp = ft_manage_shlvl(commands->envp);
}
