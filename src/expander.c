#include "../inc/minishell.h"

char    *ft_manage_expander(char **envpc, int index, char *evar)
{
    const char *equal_sign;
    
    index = ft_search_env(envpc, evar);
    if (index < 0)
    {
        return (NULL);
    }
    if (index >= 0)
    {
        equal_sign = ft_strchr(envpc[index], '=');
        if (equal_sign != NULL) 
        {
            return (ft_strdup(equal_sign + 1));
        }
    }
    return(NULL);
}

void    ft_expand(t_msh *commands)
{
    int i;

    i = ft_search_env(commands->envp, commands->evar);
    commands->evar = ft_manage_expander(commands->envp, i, commands->evar);

}

int ft_check_syntax(char *evar) 
{
    int i = 0;
    while (evar[i] != '\0') 
    {
        if (ft_isdigit(evar[0]) == 1) 
        {
            printf("error var num\n");
            exit(1);
        }
        if (ft_isalpha(evar[i]) == 0 && evar[i] != '_' && ft_isdigit(evar[i + 1]) != 0) 
        {
            printf("error, var type\n");
            exit(1);
        }
        i++;
    }
    return (0);
}

char *ft_get_var(t_msh *commands, int i) 
{
    size_t len = 0;
    char *evar;

    while (commands->input[i] != ' ' && commands->input[i] != '\0') 
    {
        i++;
        len++;
    }
    evar = malloc(len + 1);
    if (!evar)
    {
        printf("malloc failed\n");
        exit(1);
    }
    strncpy(evar, &commands->input[i - len], len);
    evar[len] = '\0';
    ft_check_syntax(evar);
    return (evar);
}

void ft_expand_var(t_msh *commands) 
{
    int i = 0;
    while (commands->input[i] != '\0') 
    {
        if (commands->input[i] == '$') 
        {
            commands->evar = ft_get_var(commands, i + 1);
            i += ft_strlen(commands->evar) + 1;
            printf("Variable de entorno: %s\n", commands->evar);
            ft_expand(commands);
            printf("Variable de entorno: %s\n", commands->evar);
        }
        i++;
    }
}
