/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:21:52 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/20 11:07:41 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*source;
	char		*dest;

	if (!dst && !src)
		return (NULL);
	dest = (char *)dst;
	source = (const char *)src;
	while (n--)
	{
		*dest++ = *source++;
	}
	return (dst);
}
