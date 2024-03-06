#include "minishell.h"

int ft_search_shlvl(char **env)
{
    int i;

    i = 0;
    while (ft_strncmp(env[i], "SHLVL=", 6) != 0)
        i++;
    return (i);
}

void    ft_free_env(char **env)
{
    int i;

    i = -1;
    while (env[++i])
        free(env[i]);
    free(env);
}
char    **ft_manage_shlvl(char **minienv)
{
    int index;
    int nb;
    char    *nbr;

    index = ft_search_shlvl(minienv);
    nb = ft_atoi(&minienv[index][6]);
    nb += 1;
    nbr = ft_itoa(nb);
    minienv[index] = ft_strjoin("SHLVL=", nbr);
    free(nbr);
    return(minienv);
}

char    **ft_copy_envp(char **envp)
{
    char    **minienv;
    int     i;
    int     count;

    count = 0;
    i = 0;
    while (envp[count])
        count++;
    minienv = (char **)malloc((count + 1) * sizeof(char *));
    if (!minienv)
        return (ft_free_env(minienv), NULL);
    while (envp[i])
    {
        minienv[i] = ft_strdup(envp[i]);
        i++;
    }
    minienv[i] = NULL;
    return (minienv);
}