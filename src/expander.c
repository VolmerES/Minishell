/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volmer <volmer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/09/07 17:57:09 by volmer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//funcion que se encarga de expandir la variable  $?, sustityuendo el valor de $?
// por el valor de last_out dentro de input
void	ft_expand_special(t_msh *commands)
{
	char	*expanded_variable;
	char	*result;
	char	*pos;

	expanded_variable = ft_itoa(commands->last_out);
	if (expanded_variable == NULL)
	{
		printf("Error: No se pudo asignar memoria.\n");
		exit(1);
	}
	pos = ft_strstr(commands->input, "$?");
	if (pos == NULL)
	{
		free(expanded_variable);
		return;
	}
	result = malloc(strlen(commands->input) - 2 + ft_strlen(expanded_variable) + 1);
	if (result == NULL)
	{
		printf("Error: No se pudo asignar memoria.\n");
		free(expanded_variable);
		exit(1);
	}
	ft_strncpy(result, commands->input, pos - commands->input, ft_strlen(commands->input) - 2 + ft_strlen(expanded_variable) + 1);
	result[pos - commands->input] = '\0';
	ft_strlcat(result, expanded_variable, ft_strlen(commands->input) - 2 + ft_strlen(expanded_variable) + 1);
	ft_strlcat(result, pos + 2, strlen(commands->input) - 2 + strlen(expanded_variable) + 1);
	free(commands->input);
	commands->input = result;
	free(expanded_variable);
}
/* Sobre escribe dentro de evar,con el valor de la variable de 
entorno y la devuelve */
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
				printf("Error: No se pudo asignar memoria.\n");
				exit(1);
			}
			return (expanded_variable);
		}
	}
	return (NULL);
}
/*Busca la variable de entorno dentro del env,
	deuvelve un indice a su posicon y copia lo que sigue al simbolo "="*/

void	ft_expand(t_msh *commands)
{
	int	i;

	i = ft_search_env(commands->envp, commands->evar);
	commands->evar = ft_manage_expander(commands->envp, i, commands->evar);
}

/*Verifica que la variable de entorno no comienze por un numero,
	y que tenga caracteres correctos*/
int	ft_check_syntax(char *evar, t_msh *commands)
{
	int	i;

	i = 0;
	while (evar[i] != '\0')
	{
		if (ft_isdigit(evar[0]) == 1)
		{
			printf("error var num\n");
			commands->last_out = 1;
			exit(1);
		}
		if (ft_isalpha(evar[i]) == 0 && evar[i] != UNDERSCORE
			&& ft_isdigit(evar[i + 1]) != 0)
		{
			printf("error, var type\n");
			commands->last_out = 1;
			exit(1);
		}
		i++;
	}
	return (0);
}

/*Esta funcion extrae la variable de entorno y la copia dentro de evar,
para despues comprobar que sea una variable de entrono correcta 
mediante syntax */
char	*ft_get_var(t_msh *commands, int i)
{
	size_t	len;
	char	*evar;

	len = 0;
	while (commands->input[i] != SPACE && commands->input[i] != '\0'
		&& commands->input[i] != DQUOTES)
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

/*Esta funcion se encarga de buscar una variable de entorno introducida 
 * en el input	si la encuentra, llama a get_var para seccionarla del 
 * resto del input, para posteriormente expandirla*/
void	ft_expand_var(t_msh *commands)
{
	int	i;

	i = 0;
	while (commands->input[i] != '\0')
	{
		if (commands->input[i] == DOLLAR && commands->input[i + 1] != SPACE
			&& commands->input[i + 1] != '\0' && commands->input[i
				+ 1] != DQUOTES && (i == 0 || commands->input[i - 1] != SQUOTES))
		{
			if (commands->input[i] == DOLLAR && commands->input[i + 1] == '?')
				ft_expand_special(commands);
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
		i++;
	}
}
