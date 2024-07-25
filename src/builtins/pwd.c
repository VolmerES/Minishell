/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:34:08 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/07/24 17:20:38 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd_builtin()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	//! poner PWD en blanco
	if(pwd){
		printf("%s\n", pwd);
		free(pwd);
	}
	
	return (0);
}