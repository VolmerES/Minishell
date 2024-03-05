/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:54:58 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2023/09/28 10:47:24 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	check_abs(long long n)
{
	long long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

static int	check_len(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				sign;
	int				len;
	char			*memory;
	unsigned int	num;

	len = 0;
	sign = 0;
	if (n < 0)
		sign = 1;
	len = check_len(n);
	memory = (char *)malloc(sizeof(char) * (len + 1));
	if (!memory)
		return (NULL);
	*(memory + len) = '\0';
	num = check_abs(n);
	while (len--)
	{
		*(memory + len) = (num % 10) + '0';
		num = num / 10;
	}
	if (sign)
		*memory = 45;
	return (memory);
}
