#include "../inc/minishell.h"

void    ft_sigint(int sign)
{
    char *get_str;
    if (sign == SIGINT)
    {
        tputs(get_str, 1, putchar);
        ft_putchar_fd('\n', 1);
    }
}

void    ft_signal_handler()
{
    signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigint);
}