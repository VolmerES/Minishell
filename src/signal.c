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

extern int		g_signal_control;

void	ctrl_c(int sign)
{
	(void)sign;
	if (g_signal_control == 0)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_control = 130;
	}
	else
	{
		g_signal_control = 130;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_4(int sign)
{
	(void)sign;
	if (g_signal_control == 2)
		return ;
	else if (g_signal_control == 1)
	{
		write(STDERR_FILENO, "^\\Quit: \n", 10);
		g_signal_control = 131;
	}
	return ;
}

void	ft_signal_handler(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_4);
}

static void	ft_heredoc_sigint(int sign)
{
	if (sign == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		exit(130);
	}
}

void	ft_heredoc_signal_handler(void)
{
	signal(SIGINT, ft_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
