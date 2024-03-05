/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:29:54 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/21 11:19:49 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str_copy;
	char	*init;

	str_copy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	init = str_copy;
	if (!str_copy)
		return (NULL);
	while (*s1)
		*str_copy++ = *s1++;
	*str_copy = '\0';
	return (init);
}
