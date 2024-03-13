#include "minishell.h"

/* ************************************************************************** */
/*  Funcion para buscar ocurrencias de los bulktins, sin el "n bytes" de la   */
/*  version de la biblioteca de la libft                                      */
/* ************************************************************************** */

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while ((str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}