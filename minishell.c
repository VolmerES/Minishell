// * Manual de BASH *  https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

/* Funcion para segmentar los comandos*/
// char    **ft_tokenizer(char *commands)
// {
//     char **matrix_commands;
//     int j = 0;
//     int i = 0;
    // Encontrar la manera de saber que separador tengo que usar;
    // Si encuentra unas comillas simples o dobles, guarde el contenido que hay dentro de ellas. 
    // Si hay un pipe, en la posicion correspondiente, guardarlo dentro dde la matriz
    // Si hay una redirireccion, separar cada comando de la lista
    // if (ft_quotes == 0)
    // {
    //     matrix_commands[i][j]
    // }
    // ft_split(commands)
//}

/* 
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
distintos a los del propio bash, puesto que se ejecutan dentro del propio bash como intrinsecos de esta 
    -Pipe: |
    -Argumentos: Son lo argumentos que se le pasan a cualquier comando. 
    -Redireccion: Por ejemplo >> 
*/

int main(int argc, char **argv, char **envp) 
{
    char *commands;

    if (argc != 1)
        return(1);
    while (1)
    {
        signal(SIGINT, ft_sigint());                                                // En este caso SIGINT, verfica si el usuario presiona ctrl+c
        commands = readline("Esperando entrada del usuario:\n");
        if (commands == NULL)
        {
           printf("No se ingresó ninguna entrada.\n");
           break;
        }
        else
        {
            add_history(commands);                                                  // Añade lo introducido por consola a un historial.
            printf("Has ingresado: %s\n", commands);                                // Comprobación de lo que se ha introducido por pantalla.
            //ft_tokenizer(commands);                                                 // Llamo a funcion para tokenizar lo que el usuario nos ha introducido por argumentos.
            system(commands);                                                       // Cochinada colosal para ir ejecutando los comandos introducidos de momento.
            free(commands);                                                         // Libera la memoria asignada por readline();
        }
    }
    write_history("Historial");                                                     // Imprime en un archivo que se crea en caso de no existir los comandos introducidos.
    return 0;
}