/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:22:41 by jdelorme          #+#    #+#             */
/*   Updated: 2024/02/22 19:10:43 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *line;

    // Espera la entrada del usuario
    while (1)
    {
        line = readline("Esperando entrada del usuario:\n");
        if (line == NULL)
        {
           printf("No se ingresó ninguna entrada.\n");
           break;
        }
        else
        {            // Guarda la entrada del usuario en el historial
            add_history(line);
            printf("Has ingresado: %s\n", line);
            system(line);
            free(line); // Libera la memoria asignada por readline();
        }
    }
    write_history("Historial");
    return 0;
}