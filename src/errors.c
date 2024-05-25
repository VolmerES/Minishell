/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:26:28 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/25 14:40:37 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_(t_err_msg error)
{
	if (error == 0)
		perror("PIPE");
	else if (error == 1)
		perror("FORK");
	else if (error == 2)
		perror("MALLOC");
	exit(1);
}