/* ***********************************IMPORTANTE*************************************** */
// * Manual de BASH *  https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html */
// * Compilar proyecto * gcc libft/libft.a minishell.c -lreadline -ltermcap             */
// * Cerrar el programa * Ctrl + D                                                      */
// * Instalar better comments en VS para ver los comentarios mas claros                 */
/* ************************************************************************************ */

#include "minishell.h"

void    ft_expand(t_msh *commands)
{
    ft_search_env(commands->envp, commands->evar);
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

    while (commands->input[i] != '=' && commands->input[i] != '\0') 
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
            i += strlen(commands->evar) + 1;
            printf("Variable de entorno: %s\n", commands->evar);
            ft_expand(commands);
            free(commands->evar);
        }
        i++;
    }
}


/* ************************************************************************** */
/*  Funcion para buscar ocurrencias de los bulktins, sin el "n bytes" de la   */
/*  version de la biblioteca de la libft                                      */
/* ************************************************************************** */

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while ((str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*  Funcion que comprueba la existencia de builtins en el input del usuario   */
/*  y llama a ejecutar el builtin indicado                                    */
// ! Falta expandir las variables antes de llamar a comparar cualquiera       */
/* ************************************************************************** */

void    ft_builtins(t_msh *commands)
{
    if (ft_strcmp(commands->input, "echo") == 0)
    {
        printf("\033[31mEjecutado echo...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "cd") == 0)
    {
        printf("\033[31mEjecutado cd...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "pwd") == 0)
    {
        printf("\033[31mEjecutado pwd...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "export") == 0)
    {
        printf("\033[31mEjecutado export...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "unset") == 0)
    {
        printf("\033[31mEjecutado unset...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "env") == 0)
    {
        printf("\033[31mEjecutado env...\033[0m\n");
    }
    if (ft_strcmp(commands->input, "exit") == 0)
    {
        printf("\033[31mEjecutado exit...\033[0m\n");
    }
}

/* *********************************************************************************** */
/*  Funcion que comprueba que en el input las comillas simples y dobles introducidas   */
/*cerradas en caso contrario no es necesario gestionarlo por ende se cierra el programa*/
/* *********************************************************************************** */

int ft_incomplete_squotes(t_msh *commands)
{
    int i;
	char quote;

    i = -1;
    quote = 0;
    while (commands->input[++i] != '\0')
    {
        if (!quote && (commands->input[i] == '\'' || commands->input[i] == '\"') 
			&& (commands->input[i - 1] != '\\' || i == 0))
			    quote = commands->input[i];
		else if (commands->input[i] == quote && commands->input[i - 1] != '\\')
			quote = '\0';
    } 
    return (quote != '\0');
}
/* ********************************************************************************** */
/*  1. Llama a comprobar si las comillas simples estan cerradas                       */
/*  2. LLama a comporbar si las comillas dobles estan cerradas                        */  
/*  3. Llama a comprobar si hay algun built-in y lo ejecuta                           */ 
/*                                                                                    *  
    ! Falta gestionar que el programa no se cierre si las comillas no estas cerradas, 
    ! no gestionar que se cierren estas, sino simplemente esperar nuevo input.
    ! Si variables globales contienen comillas, salta error cuando no debería. 
*/
/* ********************************************************************************** */

void    ft_manage(t_msh *commands)
{
    if (ft_incomplete_squotes(commands) == 1)
    {
        printf("--->Syntax error, quotes not closed\n");
        return ;
    }
    ft_expand_var(commands);
    ft_builtins(commands);

}
/* ********************************************************************************* */
/*  1. TGETSTR = intenta borrar ^C del terminal mediante "cl" (clear) (No funcoiona) */
/*  2. Si es SIGINT, imprime un salto de línea, para limpiat a terminal.             *
    ! Falta borrar ^C que se imprime en terminal al presionar las teclas...          */
/* ********************************************************************************* */

void    ft_sigint(int sign)
{
    char *get_str;
	printf("---->%i", sign);
    get_str = tgetstr("cl", NULL);
    if (sign == SIGINT)
    {
        tputs(get_str, 1, putchar);
        ft_putchar_fd('\n', 1);
    }
    // 
}
/* ******************************************************************************************************************************************************* */
/*  1. SIGINT = verifica si el usuario presiona ctrl+c;                                                                                                    */
/*  2. SIGQUIT = verifica si el usuario presiona ctrl+d;                                                                                                   */
/*  3. READLINE = Dentro de un bucle infinito, espera la entrada del usuario, y la guarda en input, asignando memoria automaticamente                      */
/*  4. ENVP = Se llama a copiar en enviroment de la shell, para despues modificar su nivel si se ejecuta una shell en una shell                            */
/*  5. FT_MANAGE = Llama a gestionar cierta parte del parseo del input                                                                                     */
/*  6. WRITE_HISTORY = Genera una arhivo de los comandos que han sido ejecutados y añadidos mediante add_history                                           *
    ! SYSTEM = Es una cochinada para que se ejecuten los comandos mientras se realiza el parseo y no la parte ejecutora del programa no esta implementada. */
/* ******************************************************************************************************************************************************* */

int main(int argc, char **argv, char **envp) 
{
    t_msh commands;

    if (argc != 1)
        return(1);
    
    commands.envp = ft_copy_envp(envp);
    commands.envp = ft_manage_shlvl(commands.envp);
    while (1)
    {
        signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigint);
        commands.input = readline("🐚Minishell-42$");
        if (commands.input == NULL)
        {
           printf("\nNo se ingresó ninguna entrada.\n");
           break;
        }
        else
        {
            // for (int i = 0; commands.envp[i]; i++)
            //     printf("\033[31m%s\033[0m\n", commands.envp[i]);
            add_history(commands.input);
            ft_manage(&commands);
            system(commands.input);
            free(commands.input);
        }
    }
    write_history("Historial");
    return 0;
}