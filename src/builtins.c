#include "../inc/minishell.h"

void    ft_builtins(t_msh *commands)
{
    if (ft_strcmp(commands->input, "echo") == 0)
    {
        printf("\033[34mEjecutado echo...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "cd") == 0)
    {
        printf("\033[34mEjecutado cd...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "pwd") == 0)
    {
        printf("\033[34mEjecutado pwd...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "export") == 0)
    {
        printf("\033[34mEjecutado export...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "unset") == 0)
    {
        printf("\033[34mEjecutado unset...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "env") == 0)
    {
        printf("\033[34mEjecutado env...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "exit") == 0)
    {
        printf("\033[34mEjecutado exit...\033[0m\n");
    }
}