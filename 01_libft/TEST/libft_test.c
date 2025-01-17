/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:29:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/17 01:26:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include "../libft.h"

//PROTOTIPOS
int		options_draw();
char	options_null_valid();
void 	fill_null(char *s1, char *s2);
char	*fill_string(char *s);
int		fill_num_bytes(char *s);
char	fill_char(char *s, int *offset);
char	fill_crash_menu();
char	output_solution(char *ft, char *orig);
char	output_solution_int(int *ft, int *orig);


int	main_memchr();
int	main_memcmp();
int	main_strchr(int opcion);
	
//EL MAIN GENERAL
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
			case '0':
				main_memchr();
				break;
			case '1':
				main_memcmp();
				break;
			case '2':
				main_strchr(1);
				break;
			case '3':
				main_strchr(2);
				break;
			case 'X':
			case 'x':
				return (0);
			default:
				printf("Opcion no valida. Ingrese una tecla valida\n");
				break;
		}
	}
	return (0);
}

///////////////////////////////////////////////////
// MENUS INPUT ////////////////////////////////////
///////////////////////////////////////////////////
//MENU DE OPCIONES GENERAL
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
	printf("%5s\n", "(0). Test ft_memchr.c");
	printf("%5s\n", "(1). Test ft_memcmp.c");
	printf("%5s\n", "(2). Test ft_strchr.c");
	printf("%5s\n", "(3). Test ft_strrchr.c");
	printf("\n%5s", "Presione letra de opcion o 'x' para salir. (Presionar <Enter>) : ");
	//while ((press = getchar()) != 10); // 10 es el enter.
	return (0);
}

//MENU DE OPCIONES NULL Y VALIDAS
char options_null_valid()
{
	system ("clear");
	printf("1. Opciones de NULL");
	printf("\n2. Opciones validas");
	printf("\nCual elige? : ");
	char c = getchar();
	while (getchar() != '\n'); //necesario para quitar el enter (\n) al pulsar el getchar
	return (c);
}

//MENU ASIGNAR NULLS VARIOS STRINGS
void fill_null(char *s1, char *s2)
{
	system ("clear");
	printf("1. S1 NULL S2 normal");
	printf("\n2. S1 normal S2 NULL");
	printf("\n3. S1 NULL S2 NULL");
	printf("\n\nCual elige? : ");
	char c = getchar();
	while (getchar() != '\n');
	switch (c){
		case '1':
			s1 = NULL;
			s2 = fill_string(s2);
			break;
		case '2':
			s1 = fill_string(s1);
			s2 = NULL;
			break;
		case '3':
			s1 = NULL;
			s2 = NULL;
			break;
		default:
			break;
	}
}

//MENU INTRODUCIR STRING
char *fill_string(char *s)
{
	system ("clear");
	printf("String = %s", s);
	printf("\nIntroduzca cadena en la que buscar : \n");
	scanf("%99s", s);
	getchar(); //libera buffer del enter = \n
	return (s);
}

//MENU PARA NUM DE BYTES A RECORRER
int	fill_num_bytes(char *s)
{
	int	num_bytes;
	system ("clear");
	printf("String = %s", s);
	printf("\nIntroduzca num de bytes a buscar : \n");
	scanf("%d", &num_bytes);
	getchar();
	return (num_bytes);
}

//MENU INTRODUCIR CHARS
char fill_char(char *s, int *offset)
{
	char c;
	system ("clear");
	printf("String = %s", s);
	printf("\nOffset para chars como \\0(-49) u Overflow: ");
	scanf("%d", offset);
	getchar();
	printf("\nIntroduzca el caracter a buscar. \\0 = '1' - 49 : \n");
	scanf("%c", &c);
	getchar();
	return (c);
}

//MENU PARA CRASHEOS
char	fill_crash_menu()
{
	printf("\nEl programa puede crashear. Elija la funcion a aplicar y luego repita con la otra para comparar");
	printf("\n\n1. ft_");
	printf("\n2. original");
	printf("\n\nopcion? : ");
	char c = getchar();
	while (getchar() != '\n');
	return (c);
}

//MENU PARA SOLUCION PUNTEROS
char	output_solution(char *ft, char *orig)
{
	printf("\nSolucion_ft   :%s", ft);
	printf("\nSolucion_orig :%s", orig);
	printf("\n\nQuiere probar de nuevo? (y / n) : ");
	char c = getchar();
	while (getchar() != '\n');
	return (c); 
}

//MENU SOLUCION INTS
char	output_solution_int(int *ft, int *orig)
{
	printf("\nSolucion_ft   :%d", *ft);
	printf("\nSolucion_orig :%d", *orig);
	printf("\n\nQuiere probar de nuevo? (y / n) : ");
	char c = getchar();
	while (getchar() != '\n');
	return (c); 
}


////////////////////////////////////////////////////////////
/*ft_memchr*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_memchr()
{
	char	*s = (char *)calloc(100, sizeof(char));
	char	c;
	int		offset;
	char	press;
	int		num_bytes;

	//Sub menu principal
	press = options_null_valid();
		
	if (press == '1')
		s = NULL;
	else
		s = fill_string(s);
			
	//MENU PARA ELEGIR NUM DE BYTES A BUSCAR
	num_bytes = fill_num_bytes(s);
		
	//Menu para elegir char
	c = fill_char(s, &offset);
		
	char	*solucion_ft;
	char	*solucion_orig;
	
	//condiciones NULL
	if (s == NULL)
	{
		while (1)
		{
			system ("clear");
			printf("String = %s", s);
			printf("\nbytes = %d", num_bytes);
			if ((c < 33) || (c > 126))
				printf("\nchar(num) = %d", c);
			else
				printf("\nchar = %c", c);
			press = fill_crash_menu();
			
			switch (press)
			{
				case '1': 
					solucion_ft = ft_memchr(s, c + offset, num_bytes);
					break;
				case '2':
					solucion_orig = memchr(s, c + offset, num_bytes);
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
		solucion_ft = ft_memchr(s, c + offset, num_bytes);
		solucion_orig = memchr(s, c + offset, num_bytes);
	}

	//SOLUCION
	system ("clear");
	printf("String = %s", s);
	if ((c < 33) || (c > 126))
		printf("\nchar(num) = %d", c);
	else
		printf("\nchar = %c", c);
	printf("\nbytes = %d", num_bytes);
	
	press = output_solution(solucion_ft, solucion_orig);
	
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		main_memchr();
		return (0);
	}
	free (s);
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_memcmp*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_memcmp()
{
	char	*s1 = (char *)calloc(100, sizeof(char));
	char	*s2 = (char *)calloc(100, sizeof(char));
	char	press;
	int		num_bytes;

	//Sub menu principal
	press = options_null_valid();
		
	if (press == '1')
		fill_null(s1, s2);
	else
	{
		s1 = fill_string(s1);
		s2 = fill_string(s2);
	}

	//MENU PARA ELEGIR NUM DE BYTES A BUSCAR
	num_bytes = fill_num_bytes(s1);
		
	int	solucion_ft;
	int	solucion_orig;
	
	//condiciones NULL
	if ((s1 == NULL) || (s2 == NULL))
	{
		while (1)
		{
			system ("clear");
			printf("String1 = %s", s1);
			printf("\nString2 = %s", s2);
			printf("\nbytes = %d", num_bytes);
			press = fill_crash_menu();
			switch (press)
			{
				case '1': 
					solucion_ft = ft_memcmp(s1, s2, num_bytes);
					break;
				case '2':
					solucion_orig = memcmp(s1, s2, num_bytes);
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
		solucion_ft = ft_memcmp(s1, s2, num_bytes);
		solucion_orig = memcmp(s1, s2, num_bytes);
	}

	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nString2 = %s", s2);
	printf("\nbytes = %d", num_bytes);
	
	press = output_solution_int(&solucion_ft, &solucion_orig);
	
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		main_memcmp();
		return (0);
	}
	free (s1);
	free (s2);
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strchr ft_strrchr*/////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strchr(int opcion)
{
	char	*s = (char *)calloc(100, sizeof(char));
	char	c;
	int		offset = 0;
	char	press;
	
	//Sub menu principal
	press = options_null_valid();
		
	if (press == '1')
		s = NULL;
	else
		s = fill_string(s);
	
	//Menu para elegir char
	c = fill_char(s, &offset);
		
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
			press = fill_crash_menu();
			
			switch (press)
			{
				case '1': 
					if (opcion == 1)
						solucion_ft = ft_strchr(s,c + offset);
					else if (opcion == 2)
						solucion_ft = ft_strrchr(s,c + offset);
					break;
				case '2':
					if (opcion == 1)
						solucion_orig = strchr(s,c + offset);
					else if (opcion == 2)
						solucion_orig = strrchr(s,c + offset);
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
		if (opcion == 1)
		{	
			solucion_ft = ft_strchr(s,c + offset); //+offset por que si no es convertida y no vale la prueba
			solucion_orig = strchr(s,c + offset);
		}
		if (opcion == 2)
		{
			solucion_ft = ft_strrchr(s,c + offset);
			solucion_orig = strrchr(s,c + offset);
		}
	}
	
	//SOLUCION
	system ("clear");
	printf("String = %s", s); //
	if ((c < 33) || (c > 126)) //no print
		printf("\nchar(num) = %d", c); //char en int
	else
		printf("\nchar = %c", c);
	
	press = output_solution(solucion_ft, solucion_orig);
	
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		if (opcion == 1)
			main_strchr(1);
		else if (opcion == 2)
			main_strchr(2);
		return (0); //si no puede ir al otro free y liberar de nuevo. NO SE COMO. Supongo que por recursividad
	}
	free (s);
	s = NULL; //proteccion frente a doble free
	return (0);
}


