/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:29:21 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/25 15:35:24 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_sub(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (*(str + i) && *(str + i) != c)
		i++;
	return (i);
}

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

static size_t	count_sub(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (count);
}

static char	**split_str(char const *s, char c, char **array, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(array + i) = ft_substr(s, j, len_sub(&*(s + j), c));
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	count_sub_str;

	if (!s)
		return (NULL);
	count_sub_str = count_sub(s, c);
	array = (char **)malloc(sizeof(char *) * (count_sub_str + 1));
	if (!array)
		return (NULL);
	array = split_str(s, c, array, count_sub_str);
	return (array);
}
