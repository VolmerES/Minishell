/* ************************************************************************** */
/*                                                                            */
/*   singal.c                                             :::      ::::::::   */
/*                                     					:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/04/15 13:11:30 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_sigint(int sign)
{
	if (sign == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("🐚Minihell-42", 1);
	}
}
void	ft_sigquit(int sign)
{
	if (sign == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signal_handler(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
}
