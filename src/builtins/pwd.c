/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:34:08 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/07/29 20:22:26 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd_builtin(t_msh *commands)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if(pwd){
		printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		update_env(commands, ft_search_env(commands->envp, "PWD"), "PWD=");
	}
	
	return (0);
}