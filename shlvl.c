#include "minishell.h"

char **ft_addVariable(char **minienv, char *aux)
{
    char **matrix;
    int i;

    i = 0;
    while (minienv[i])
        i++;
    matrix = (char **)malloc((i + 2) * sizeof(char *));
    matrix[i++] = aux;
    matrix[i] = NULL;
    ft_free_matrix(minienv);
    return (matrix);
}

int ft_search_env(char **env, char *tofind)
{
    int i;
    char    **spl;

    i = 0;
    while (env[i])
    {
        spl = ft_split(env[i], '=');
        if (ft_strcmp(spl[0], tofind) == 0)
            return (ft_free_matrix(spl), i);
        
        i++;
    }
    return (-1);
}

void    ft_free_matrix(char **env)
{
    int i;

    i = -1;
    while (env[++i])
        free(env[i]);
    free(env);
}

/* ************************************************************************************* */
/*  Manage_shlvl, busca la posicion de SHLVL en env, mediante search_shlvl, modifica su  */
/*  valor numerico, y lo vuelve a sobreescribir mediante strjoin                         */
/* ************************************************************************************* */

char    **ft_manage_shlvl(char **minienv)
{
    int index;
    int nb;
    char    *nbr;
    char    *aux;
    
    index = ft_search_env(minienv, "SHLVL");
    if (index == -1)
    {
        aux = ft_strdup("SHLVL=1");
        minienv = ft_addVariable(minienv, aux);
    }
    if (index <= 0)
    {
        nb = ft_atoi(&minienv[index][5]);
        nb += 1;
        nbr = ft_itoa(nb);
        free(minienv[index]);
        minienv[index] = ft_strjoin("SHLVL=", nbr);
        free(nbr);
    }
    return(minienv);
}

/* ************************************************************************************* */
/*  Copy_env, reserva memoria y copia dentro de la struct el entorno para posteriormente */
/*  realizar cambios en el valor del nivel de la SHELL, variable en env-->  SHLVL= nb    */
/* ************************************************************************************* */

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
        return (ft_free_matrix(minienv), NULL);
    while (envp[i])
    {
        minienv[i] = ft_strdup(envp[i]);
        i++;
    }
    minienv[i] = NULL;
    return (minienv);
}