// * Manual de BASH *  https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html
// * Compilar proyecto * gcc libft/libft.a minishell.c -lreadline -ltermcap
// * Cerrar el porgrama * Escribir kill, sino queda proceso en segundo plano.

                                      // Necesaria para tgetstr
#include "minishell.h"    


/*  Funcion que comprueba que en el imput la comillas doble introducidas sean estes 
cerradas en caso contrario no es necesario gestionarlo por ende se cierra el programa. */

int ft_incomplete_dquotes(t_msh *commands)
{
    int i;
    int q;

    q = 0;
    i = 0;
    while (commands->input[i] != '\0')
    {
        if (commands->input[i] == '\"')
            q++;
        i++;
    }
    if (q % 2 != 0)
        return (1);
    else
        return (0);
}

/*  Funcion que comprueba que en el imput la comillas simples introducidas sean estes 
cerradas en caso contrario no es necesario gestionarlo por ende se cierra el programa. */

int ft_incomplete_squotes(t_msh *commands)
{
    int i;
    int q;

    q = 0;
    i = 0;
    while (commands->input[i] != '\0')
    {
        if (commands->input[i] == '\'')
            q++;
        i++;
    }
    if (q % 2 != 0)
        return (1);
    else
        return (0);
}

/*  1. Llama a comprobar si las comillas simples estan cerradas
    2. LLama a comporbar si las comillas dobles estan cerradas 
    3. Llama a comprobar si hay algun built-in                  */
void    ft_manage(t_msh *commands)
{

// ! Falta gestionar que el programa no se cierre si las comillas no estas cerradas, 
// ! no gestionar que se cierren estas, sino simplemente esperar nuevo input.

    if (ft_incomplete_squotes(commands) == 1) //Comprobar si las comillas estan completas, sino return;
    {
        printf("Syntax error, simple quotes not closed");
        return ;
    }
    if (ft_incomplete_dquotes(commands) == 1)
    {
        printf("Syntax error, double quotes not closed");
        return ;
    }
    
}
void    ft_sigint(int sign)
{
    char *get_str;

    get_str = tgetstr("cl", NULL);
    if (sign == SIGINT)
    {
        tputs(get_str, 1, putchar);
        ft_putchar_fd('\n', 1);                                                 // Imprime un salto de linea cuando el usuario presiona ctrl + c.
    }
    // ! Falta borrar ^C que se imprime en terminal al presionar las teclas...
}
int main(int argc, char **argv, char **envp) 
{
    t_msh *commands;

    if (argc != 1)
        return(1);
    while (1)
    {
        signal(SIGINT, ft_sigint);                                                // En este caso SIGINT, verfica si el usuario presiona ctrl+c
        commands->input = readline("Esperando entrada del usuario:\n");
        if (commands->input == NULL)
        {
           printf("No se ingresó ninguna entrada.\n");
           break;
        }
        else
        {
            add_history(commands->input);                                                  // Añade lo introducido por consola a un historial.
            //printf("Has ingresado: %s\n", commands);                                // Comprobación de lo que se ha introducido por pantalla.
            ft_manage(commands);                                                 // Llamo a funcion para tokenizar lo que el usuario nos ha introducido por argumentos.
            //system(commands->input);                                                       // Cochinada colosal para ir ejecutando los comandos introducidos de momento.
            free(commands->input);                                                         // Libera la memoria asignada por readline();
        }
    }
    write_history("Historial");                                                     // Imprime en un archivo que se crea en caso de no existir los comandos introducidos.
    return 0;
}

/* 
^
|
|
|
Esta funcion al ejecutar programa se queda a la espera de una entrada por la linea de comandos (ver readline)
La idea actual es tokenizar los argumentos pasados de manera que se pueda trabajar por separado para 
identificarlos. Tokenizar se traduce en segmentarlos por partes, y meterlos dentro de una estrucutura
asignandoles un tipo de dato(argumento, flag, pipe, builtin).
Véase:  echo "Hola mundo"  = 2 TOKENS
        echo Hola mundo = 3 TOKENS
        echo "Hola mundo"hola = 2 TOKENS 
        
Estos TOKENS, van a ser guardados, primero, en una matriz ** y posteriormente en una estructura de datos para, que va a contenter el segmento de la linea
de comando correpondiente, y el tipo de dato que son.
Estos serían los siguientes tipos de datos a clasificar: 
    -Builtin: Comandos propias de la shell, como cd, export o exit. Estos tienen un path, donde se encuentra instalado el programa pero pueden tener comportamientos
distintos a los del propio bash, puesto que se ejecutan dentro  del propio bash como intrinsecos de esta 
    -Pipe: |
    -Argumentos: Son lo argumentos que se le pasan a cualquier comando. 
    -Redireccion: Por ejemplo >> 
*/