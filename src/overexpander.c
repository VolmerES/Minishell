#include "../inc/minishell.h"


char *ft_get_env_var_value(const char *var_name)
{
    char *var_value;

    var_value = getenv(var_name);
    if (var_value == NULL)
    {
        // The environment variable does not exist.
        // Return an empty string or handle this case as needed.
        var_value = "";
    }

    return (var_value);
}
char *ft_get_var_name(char *input, int *i)
{
    int var_len = 1;

    while (input[*i + var_len] != SPACE && input[*i + var_len] != '\0' && input[*i + var_len] != DOLLAR)
        var_len++;
    return (ft_substr(input, *i + 1, var_len - 1));
}

void ft_replace_var_with_value(t_msh *commands, char *var_value, int i, int var_len)
{
    char *before;
    char *after;
    char *temp;

    before = ft_substr(commands->input, 0, i);
    after = ft_substr(commands->input, i + var_len, ft_strlen(commands->input) - (i + var_len));
    temp = ft_strjoin(before, var_value);
    free(commands->input);
    commands->input = ft_strjoin(temp, after);
    free(temp);
    free(before);
    free(after);
}
/* Recorre */
void ft_overwrited_expand(t_msh *commands)
{
    int i;
    
    i = 0;
    while (commands->input[i] != '\0')
    {
        if (commands->input[i] == DOLLAR && commands->input[i + 1] != '\0')
        {
            char *var_name = ft_get_var_name(commands->input, &i);
            char *var_value = ft_strdup(ft_get_env_var_value(var_name));
            ft_replace_var_with_value(commands, var_value, i, ft_strlen(var_name) + 1);
            free(var_name);
            free(var_value);
            i += ft_strlen(var_value) - 1;
        }
        i++;
    }
}
