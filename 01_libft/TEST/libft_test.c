/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:29:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/16 00:43:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>




int main_memcpy ();

int main()
{
    char	press = '\0';
	struct winsize w;

	system("clear");	

	//obtiene el tamanyo de la ventana
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
		return (1);
	int swidth = w.ws_col; //ancho de pantalla en chars
	char	*titulo = "OPCIONES";
	int		s_titulo = (swidth - strlen(titulo)) / 2 ;

	//impresion
	printf("%*s%s\n", s_titulo, "", titulo);
	printf("%5s\n", "(a). Test ft_atoi.c");
	printf("%5s\n", "(b). Test ft_memcpy.c");
	printf("%5s\n", "(c). Test ft_memmove.c");
	printf("\n%5s\n", "Presione letra de opcion o 'y' mas <enter> para salir");
	//while ((press = getchar()) != 10); // 10 es el enter.
	
	press = getchar();
	while (getchar() != '\n');
	
	switch (press)
	{
	case 'b':
		main_memcpy();
		break;
	
	default:
		break;
	}

	return (0);
}

/*ft_memcpy*/
int main_memcpy ()
{
	unsigned char *source1 = NULL;
	unsigned char *source2 = NULL;
	unsigned char *dest1 = NULL;
	unsigned char *dest2 = NULL;
	int num = 0;
	printf("\nfuncion memcpy\n");
	/*
	ft_memcpy(dest1, source1, num);
	memcpy(dest2, source2, num);
	printf("ft_: %s", dest1);
	printf("\nori: %s", dest2);
	printf("\nfinal de programa");
	*/
	return (0);
}
