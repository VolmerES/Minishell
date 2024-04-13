#include "../../inc/minishell.h"

void	ft_builtins(t_msh *commands)
{
	int i;
	char *ptr[] = {"DAVID=123", "DAVID=1234", NULL};

	i = 0;

	
	commands->cmds[0]->args = ptr;
	// cd_builtin(commands, i);
	// pwd_builtin();
	export_builtin(commands, i);

	// while (commands->cmds[i])
	// {
	// 	if (ft_strcmp(commands->cmds[i]->cmd, "cd"))
	// 		cd_builtin(commands, i);
	// 	else if (ft_strcmp(commands->cmds[i]->cmd, "pwd"))
	// 		pwd_builtin(commands, i);
	// 	else if (ft_strcmp(commands->cmds[i]->cmd, "export"))
	// 		pwd_builtin(commands, i);
	// }


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
