/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:56:08 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/25 11:25:57 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check(char const *set, char const c)
{
	size_t	i;

	if (!set)
		return (0);
	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (*(s1 + start) && check(set, *(s1 + start)))
		start++;
	end = ft_strlen(s1);
	while (end > start && check(set, *(s1 + (end - 1))))
		end--;
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (NULL);
	i = 0;
	while ((start + i) < end)
	{
		*(trim + i) = *(s1 + (start + i));
		i++;
	}
	*(trim + i) = '\0';
	return (trim);
}
