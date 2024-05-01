#include "../../inc/minishell.h"

void	ft_builtins(t_msh *commands)
{
	int i;
	// char *ptr[] = {ft_strdup("DAVID=123"), ft_strdup("DAVID=1234"), ft_strdup("lpastor=old"), ft_strdup("lpastor=new"), ft_strdup("DAVID=ldiaz-ra"), NULL};

	i = 0;

	
	// commands->cmds[0]->args = ptr;
	// cd_builtin(commands, i);
	// pwd_builtin();
	// export_builtin(commands, i);
	// export_builtin(commands, i);

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


    // if (ft_strcmp(commands->input, "echo") == 0)
    // {
    //     printf("\033[34mEjecutado echo...\033[0m\n");
    // }
    // if (ft_strcmp(commands->input, "export") == 0)
    // {
    //     printf("\033[34mEjecutado export...\033[0m\n");
    // }
    // if (ft_strcmp(commands->input, "unset") == 0)
    // {
    //     printf("\033[34mEjecutado unset...\033[0m\n");
    // }
    // if (ft_strcmp(commands->input, "env") == 0)
    // {
    //     printf("\033[34mEjecutado env...\033[0m\n");
    // }
    // if (ft_strcmp(commands->input, "exit") == 0)
    // {
    //     printf("\033[34mEjecutado exit...\033[0m\n");
    // }
}
