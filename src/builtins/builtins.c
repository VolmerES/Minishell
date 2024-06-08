#include "../../inc/minishell.h"

void	ft_builtins(t_msh *commands, int i)
{
	while (commands->cmds[i])
	{
		if (ft_strcmp(commands->cmds[i]->cmd_main, "cd") == 0)
			cd_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "pwd") == 0)
			commands->last_out = pwd_builtin();
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "export") == 0)
			export_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "echo") == 0)
			commands->last_out = echo_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "unset") == 0)
			commands->last_out = unset_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "env") == 0)
			commands->cp_stdout = env_builtin(commands);
		i++;
	}
}

int	is_builtins(t_msh *commands, int i)
{
	while (commands->cmds[i])
	{
		if (ft_strcmp(commands->cmds[i]->cmd_main, "cd") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "pwd") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "export") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "echo") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "unset") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "env") == 0)
			return (1);
		i++;
	}
	return (0);
}
