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
int ft_incomplete_quotes(t_msh *commands)
{
    int i;
	char quote;

    i = -1;
    quote = 0;
    while (commands->input[++i] != '\0')
    {
        if (!quote && (commands->input[i] == SQUOTES || commands->input[i] == DQUOTES) 
			&& (commands->input[i - 1] != BACKSLASH || i == 0))
			    quote = commands->input[i];
		else if (commands->input[i] == quote && commands->input[i - 1] != '\\')
			quote = '\0';
    } 
    return (quote != '\0');
}
void    ft_manage(t_msh *commands)
{
    if (ft_incomplete_quotes(commands) == 1)
    {
        printf("\033[34mSyntax error, quotes not closed\033[0m\n");
        return ;
    }
    ft_expand_var(commands);
    ft_builtins(commands);

}
void    ft_sigint(int sign)
{
    char *get_str;
    if (sign == SIGINT)
    {
        tputs(get_str, 1, putchar);
        ft_putchar_fd('\n', 1);
    }
}
void    ft_init_struct(t_msh *commands)
{
    commands->cmd = NULL;
    commands->envp = NULL;
    commands->evar = NULL;
    commands->input = NULL;
}
void    ft_shlvl(t_msh *commands, char **envp)
{
    commands->envp = ft_copy_envp(envp);
    commands->envp = ft_manage_shlvl(commands->envp);
}
void    ft_handle_readline(t_msh *commands)
{
    while (1)
    {
        signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigint);
        commands->input = readline("🐚Minishell-42$");
        if (commands->input == NULL)
        {
           printf("\nNo se ingresó ninguna entrada.\n");
           break;
        }
        else
        {
            add_history(commands->input);
            ft_manage(commands);
            system(commands->input);
            free(commands->input);
        }
    }
}
int main(int argc, char **argv, char **envp) 
{
    t_msh commands;

    if (argc != 1 || !argv)
        return(1);
    ft_init_struct(&commands);
    ft_shlvl(&commands, envp);
    ft_handle_readline(&commands);
    write_history("Historial");
    return 0;
}