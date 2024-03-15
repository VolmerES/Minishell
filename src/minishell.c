#include "../inc/minishell.h"

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
    ft_parse_input(commands);
}

void    ft_init_struct(t_msh *commands)
{
    commands->cmds = NULL;
    commands->envp = NULL;
    commands->evar = NULL;
    commands->input = NULL;
}

void    ft_handle_readline(t_msh *commands)
{
    while (1)
    {
        ft_signal_handler();
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
void ft_logo()
{
printf("\033[38;2;255;69;0m			   ,    \n");
    printf("\033[38;2;255;140;0m         /( /\\ )\\  _\\ \\_/ /_ \n");
    printf("\033[38;2;255;165;0m         |\\_||_/| < \\_   _/ >\n");
    printf("\033[38;2;255;215;0m         \\______/  \\|0   0|/\n");
    printf("\033[38;2;255;255;0m           _\\/ _   _(_  ^  _)_\n");
    printf("\033[38;2;255;215;0m          ( () ) /`\\|V\"\"\"V|/`\\\n");
    printf("\033[38;2;255;165;0m            {}   \\  \\_____/  /\n");
    printf("\033[38;2;255;140;0m   *        ()   /\\   )=(   /\\       \n");
    printf("\033[38;2;255;69;0m (  `       {}  /  \\_/_/\\_/\\_/  \\                  \n");
    printf("\033[38;2;255;140;0m)\\))(    (            (    ( /(     (    )\\   )\\  \n");
    printf("\033[38;2;255;165;0m((_)()\\   )\\    (      )\\   )\\())   ))\\  ((_) ((_) \n");
    printf("\033[38;2;255;215;0m(_()((_) ((_)   )\\ )  ((_) ((_)    /((_)  _    _   \n");
    printf("\033[38;2;255;255;0m|  \\/  |  (_)  _(_/(   (_) | |(_) (_))   | |  | |  \n");
    printf("\033[38;2;255;215;0m| |\\/| |  | | | ' \\))  | | | ' \\  / -_)  | |  | |  \n");
    printf("\033[38;2;255;165;0m|_|  |_|  |_| |_||_|   |_| |_||_| \\___|  |_|  |_|  \n");
    printf("\033[38;2;255;69;0m                                                    \n");
    printf("\033[38;2;255;0;0m          By: ldiaz-ra && jdelorme                           \n");
        printf("\033[38;2;255;140;0m           (As beatiful as a hell)                   \n");
    printf("\033[0m                                      \n");
}
int main(int argc, char **argv, char **envp) 
{
    t_msh commands;

    if (argc != 1 || !argv)
        return(1);
    ft_logo();
    ft_init_struct(&commands);
    ft_shlvl(&commands, envp);
    ft_handle_readline(&commands);
    write_history("Historial");
    return 0;
}