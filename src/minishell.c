/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/05/02 16:47:58 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_incomplete_quotes(t_msh *commands)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (commands->input[++i] != '\0')
	{
		if (!quote && (commands->input[i] == SQUOTES
				|| commands->input[i] == DQUOTES) && (commands->input[i
					- 1] != BACKSLASH || i == 0))
			quote = commands->input[i];
		else if (commands->input[i] == quote && commands->input[i - 1] != '\\')
			quote = '\0';
	}
	return (quote != '\0');
}

void	ft_manage(t_msh *commands)
{
	if (ft_incomplete_quotes(commands) == 1)
	{
		printf("\033[34mSyntax error, quotes not closed\033[0m\n");
		return ;
	}
	ft_expand_var(commands);
	ft_parse_input(commands);
	ft_tokenize(commands);
	int i = 0;
	int o = 0;
	while (commands->cmds[o])
	{
		printf("\033[34mMain commands fuera bucle: [%s]\033[0m\n", commands->cmds[o]->cmd_main);
		o++;
	}
	while (commands->cmds[0]->args[i])
	{
		printf("Arg fuera bucle %s\n", commands->cmds[0]->args[i]);
		i++;
	}
	i = 0;
	// while (commands->cmds[1]->args[i])
	// {
	// 	printf("Arg fuera bucle %s\n", commands->cmds[0]->args[i]);
	// 	i++;
	// }
	executor_manage(commands);
	// ft_builtins(commands);
}

void	ft_init_msh_struct(t_msh *commands)
{
	commands->cmds = NULL;
	commands->envp = NULL;
	commands->evar = NULL;
	commands->input = NULL;
}

void	ft_handle_readline(t_msh *commands)
{
	while (1)
	{
		ft_signal_handler();
		commands->input = readline("🐚Minihell-42.>");
		if (commands->input == NULL)
		{
			printf("\nNo se ingresó ninguna entrada.\n");
			break ;
		}
		else
		{
			add_history(commands->input);
			ft_manage(commands);
			//system(commands->input);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	commands;

	if (argc != 1 || !argv)
		return (1);
	ft_logo();
	ft_init_msh_struct(&commands);
	ft_shlvl(&commands, envp);
	ft_handle_readline(&commands);
	write_history("Historial");
	return (0);
}
