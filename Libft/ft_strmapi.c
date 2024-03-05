/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:49:19 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/28 11:32:22 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*memory;

	i = 0;
	len = ft_strlen(s);
	memory = (char *)malloc(sizeof(char) * (len + 1));
	if (!memory)
		return (NULL);
	while (*(s + i))
	{
		*(memory + i) = f(i,*(s + i));
		i++;
	}
	*(memory + i) = '\0';
	return (memory);
}
