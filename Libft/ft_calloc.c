/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:40:28 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/25 13:05:57 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	memory = (void *)malloc(count * size);
	if (!memory)
		return (NULL);
	else
	{
		if (!size)
			return ((void *)memory);
		else
		{
			ft_bzero (memory, (count * size));
			return ((void *)memory);
		}
	}
}
