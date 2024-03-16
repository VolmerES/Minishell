#include "../inc/minishell.h"

void    ft_builtins(t_msh *commands)
{
	char s[100];
	printf("%s\n", getcwd(s, 100)); 
	chdir("..");
	printf("%s\n", getcwd(s, 100)); 
	// printf("%s\n", ); 

	// int i;

	// i = 0;
	// while (commands->cmds[i])
	// {
	// 	if (ft_strcmp(commands->cmds[i]->cmd, "cd"))
	// 	{

	// 	}
	// }
	
    // if (ft_strcmp(commands->input, "echo") == 0)
    // {
    //     printf("\033[34mEjecutado echo...\033[0m\n");
    // }
    // if (ft_strcmp(commands->input, "cd") == 0)
    // {
        
    // }
    // if (ft_strcmp(commands->input, "pwd") == 0)
    // {
    //     printf("\033[34mEjecutado pwd...\033[0m\n");
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