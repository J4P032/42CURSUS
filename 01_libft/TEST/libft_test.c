/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:29:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/16 17:24:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include "../libft.h"

int	options_draw();
int	main_memcpy();
int	main_strchr();		

int main()
{
    char	press = '\0';
	while (1)
	{
		options_draw();
		press = getchar();
		while (getchar() != '\n');

		switch (press)
		{
			case '1':
				main_strchr();
				break;
			case 'Y':
			case 'y':
				return (0);
			default:
				printf("Opcion no valida. Ingrese una tecla valida\n");
				break;
		}
	}
	return (0);
}

int	options_draw()
{
	system("clear");	
	struct winsize w;

	//obtiene el tamanyo de la ventana
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
		return (1);
	int swidth = w.ws_col; //ancho de pantalla en chars
	char	*titulo = "OPCIONES";
	int		s_titulo = (swidth - strlen(titulo)) / 2 ;

	//impresion
	printf("%*s%s\n", s_titulo, "", titulo);
	printf("%5s\n", "(0). Test ft_atoi.c");
	printf("%5s\n", "(1). Test ft_strchr.c");
	printf("%5s\n", "(2). Test ft_memcpy.c");
	printf("%5s\n", "(3). Test ft_memmove.c");
	printf("\n%5s", "Presione letra de opcion o 'y' mas <enter> para salir : ");
	//while ((press = getchar()) != 10); // 10 es el enter.
	return (0);
}




////////////////////////////////////////////////////////////
/*ft_strchr*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strchr()
{
	char	*s = (char *)malloc(100 * sizeof(char));
	char	c;
	int		offset;
	char	press;
	
	//Sub menu principal
	system ("clear");
	printf("1. Opciones de NULL");
	printf("\n2. Opciones validas");
	printf("\nCual elige? : ");
	press = getchar();
	while (getchar() != '\n'); //necesario para quitar el enter (\n) al pulsar el getchar
	
	if (press == '1')
	{
		system ("clear");
		s = NULL;
	}
	else
	{
		system ("clear");
		printf("String = %s", s); //
		printf("\nIntroduzca cadena en la que buscar : \n");
		scanf("%99s", s);
		getchar(); //libera buffer del enter = \n
	}
	
	//Menu para elegir char
	system ("clear");
	printf("String = %s", s); //
	printf("\nOffset para chars como \\0 u Overflow: ");
	scanf("%d", &offset);
	getchar();
	printf("\nIntroduzca el caracter a buscar : \n");
	scanf("%c", &c);
	getchar();
		
	char	*solucion_ft;
	char	*solucion_orig;
	
	//condiciones NULL
	if (s == NULL)
	{
		
		while (1)
		{
			system ("clear");
			printf("String = %s", s); //
			if ((c < 33) || (c > 126)) //no print
				printf("\nchar(num) = %d", c); //char en int
			else
				printf("\nchar = %c", c);
			printf("\nEl programa puede crashear. Elija la funcion a aplicar y luego repita con la otra para comparar");
			printf("\n\n1. ft_strchr");
			printf("\n2. strchr original");
			printf("\n\nopcion? : ");
		
			press = getchar();
			while (getchar() != '\n');
			switch (press)
			{
				case '1': 
					solucion_ft = ft_strchr(s,c + offset);
					break;
				case '2':
					solucion_orig = strchr(s,c + offset);
					break;
				default:
					continue;
			}
			break;
		}
	}
	
	//condiciones Normales
	else
	{
		solucion_ft = ft_strchr(s,c + offset); //+offset por que si no es convertida y no vale la prueba
		solucion_orig = strchr(s,c + offset);
	}
	
	//SOLUCION
	system ("clear");
	printf("String = %s", s); //
	if ((c < 33) || (c > 126)) //no print
		printf("\nchar(num) = %d", c); //char en int
	else
		printf("\nchar = %c", c);
	printf("\nSolucion_ft   :%s", solucion_ft);
	printf("\nSolucion_orig :%s", solucion_orig);
	printf("\n");
	printf("Quiere probar de nuevo? (y / n) : ");
	press = getchar();
	while (getchar() != '\n'); 
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		main_strchr();
	}
	free (s);
	return (0);
}




////////////////////////////////////////////////////////////
/*ft_memcpy*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_memcpy ()
{
	//unsigned char *source1 = NULL;
	//unsigned char *source2 = NULL;
	//unsigned char *dest1 = NULL;
	//unsigned char *dest2 = NULL;
	//int num = 0;
	printf("\nfuncion memcpy\n");
	/*
	ft_memcpy(dest1, source1, num);
	memcpy(dest2, source2, num);
	printf("ft_: %s", dest1);
	printf("\nori: %s", dest2);
	printf("\nfinal de programa");
	*/
	while (getchar() != 10);
	return (0);
}
