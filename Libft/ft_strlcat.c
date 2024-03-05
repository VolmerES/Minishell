/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:09:01 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/20 12:12:45 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dest_len;
	size_t		total_len;
	const char	*s;

	if ((!dst || !src) && !dstsize)
		return (0);
	s = src;
	dest_len = ft_strlen(dst);
	if (dest_len < dstsize)
		total_len = dest_len + ft_strlen(s);
	else
		return (dstsize + ft_strlen(s));
	while (*s && (dest_len + 1) < dstsize)
	{
		*(dst + dest_len) = *s++;
		dest_len++;
	}
	*(dst + dest_len) = '\0';
	return (total_len);
}
