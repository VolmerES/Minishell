/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:28:57 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/22 10:48:56 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_new;
	char	*init;

	if (!s1 && !s2)
		return (NULL);
	str_new = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	init = str_new;
	if (!str_new)
		return (NULL);
	while (*s1)
		*str_new++ = *s1++;
	while (*s2)
		*str_new++ = *s2++;
	*str_new = '\0';
	return (init);
}
