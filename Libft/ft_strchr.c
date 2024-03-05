/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:07 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/20 10:46:55 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	character;
	int		slen;
	int		i;

	slen = ft_strlen(s);
	character = (char)c;
	i = 0;
	while (i <= slen)
	{
		if (s[i] == character)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
