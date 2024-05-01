#include "../../inc/minishell.h"

void	ft_builtins(t_msh *commands)
{
	int i;

	i = 0;
	while (commands->cmds[i])
	{
		if (ft_strcmp(commands->cmds[i]->cmd_main, "cd") == 0)
			cd_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "pwd") == 0)
			pwd_builtin();
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "export") == 0)
			export_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "echo") == 0)
			echo_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "unset") == 0)
			unset_builtin(commands, i);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "env") == 0)
			env_builtin(commands);
		else
			executor_manage(commands, i);
		i++;
	}
}
