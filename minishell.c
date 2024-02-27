/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:22:41 by jdelorme          #+#    #+#             */
/*   Updated: 2024/02/27 14:08:33 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//! Instalar Better Comments en VSCode para poder ver todo más claramente
//! |||||||  LINKS IMPORTANTES |||||||||
// * Manual de BASH *  https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html



#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"


/* Funcion para segmentar los comandos*/
char    **ft_tokenizer(char *commands)
{
    char **matrix_commands;
    int j = 0;
    int i = 0;
    // Encontrar la manera de saber que separador tengo que usar;
    // Si encuentra unas comillas simples o dobles, guarde el contenido que hay dentro de ellas. 
    // Si hay un pipe, en la posicion correspondiente, guardarlo dentro dde la matriz
    // Si hay una redirireccion, separar cada comando de la lista
    if (ft_quotes == 0)
    {
        matrix_commands[i][j]
    }
    ft_split(commands)
    
}

/* Esta funcion al ejecutar programa se queda a la espera de una entrada por la linea de comandos (ver readline)
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

int main() {
    char *commands;

    // Espera la entrada del usuario
    while (1)
    {
        commands = readline("Esperando entrada del usuario:\n");
        if (commands == NULL)
        {
           printf("No se ingresó ninguna entrada.\n");
           break;
        }
        else
        {
            add_history(commands);  // Guarda la entrada del usuario en el historial.
            printf("Has ingresado: %s\n", commands);
            ft_tokenizer(commands); //Llamo a funcion para tokenizar lo que el usuario nos ha introducido por argumentos.
            system(commands); // Cochinada colosal para ir ejecutando los comandos introducidos de momento.
            free(commands); // Libera la memoria asignada por readline();
        }
    }
    write_history("Historial"); // Imprime en un archivo que se crea en caso de no existir los comandos introducidos.
    return 0;
}