/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:29:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/21 14:00:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h> //tambien system("clear"), malloc...
#include <sys/ioctl.h> //para ioctl. obtener tamanyo de un terminal pantalla.
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "../libft.h"

//PROTOTIPOS funciones print
void	ft_print(char *str, size_t l);
void	ft_printf(char *str);
int		options_draw();
char	options_null_valid();
char 	fill_null();
char	*fill_string(char *s);
int		fill_num_bytes(char *s);
int		fill_num_sizet();
char	fill_char(char *s, int *offset);
char	fill_crash_menu();
char	output_solution(char *ft, char *orig);
char	output_solution_int(int *ft, int *orig);
void	output_solucion_ptr(void *ft, void *orig, size_t length);
char	repetimos_volvemos();

//MAIN SECUNDARIAS prototipos
int	main_atoi();
int	main_calloc();
int	main_memchr();
int	main_memcmp();
int	main_memcpy();
int	main_memmove();
int main_memset();
int main_strdup();
int	main_strchr(int opcion);
int	main_strjoin();
int main_strtrim();
int	main_substr();
int main_uplow(int (*f)(int), int (*g)(int));

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
				main_atoi();
				break;
			case '1':
				main_calloc();
				break;
			case '2':
				main_memchr();
				break;
			case '3':
				main_memcmp();
				break;
			case '4':
				main_memcpy();
				break;
			case '5':
				main_memmove();
				break;
			case '6':
				main_memset();
				break;
			case '7':
				main_strdup();
				break;
			case '8':
				main_strchr(1);
				break;
			case '9':
				main_strjoin();
				break;
			case 'a':
				main_strchr(2);
				break;
			case 'b':
				main_strtrim();
				break;
			case 'c':
				main_substr();
				break;
			case 'd':
				main_uplow(ft_tolower, tolower);
				break;
			case 'e':
				main_uplow(ft_toupper, toupper);
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

//PRINT CON WRITE detectando \0 con #.
void	ft_print(char *str, size_t l)
{
	size_t i = 0;

	while (i < l)
	{
		if (str[i] == '\0')
		{
			write(1, "#.", 2);
			i++;
		}
		else
			write(1, &str[i++], 1);
	}
}

//PRINT CON WRITE como printf para respetar el orden de los write en mains
void	ft_printf(char *str)
{
	size_t	i  = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

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
	printf("%5s\n", "(0). Test ft_atoi.c");
	printf("%5s\n", "(1). Test ft_calloc.c");
	printf("%5s\n", "(2). Test ft_memchr.c");
	printf("%5s\n", "(3). Test ft_memcmp.c");
	printf("%5s\n", "(4). Test ft_memcpy.c");
	printf("%5s\n", "(5). Test ft_memmove.c");
	printf("%5s\n", "(6). Test ft_memset.c");
	printf("%5s\n", "(7). Test ft_strdup.c");
	printf("%5s\n", "(8). Test ft_strchr.c");
	printf("%5s\n", "(9). Test ft_strjoin.c");
	printf("%5s\n", "(a). Test ft_strrchr.c");
	printf("%5s\n", "(b). Test ft_strtrim.c");
	printf("%5s\n", "(c). Test ft_substr.c");
	printf("%5s\n", "(d). Test ft_tolower.c");
	printf("%5s\n", "(e). Test ft_toupper.c");
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
char fill_null()
{
	system ("clear");
	printf("1. S1 NULL S2 normal");
	printf("\n2. S1 normal S2 NULL");
	printf("\n3. S1 NULL S2 NULL");
	printf("\n\nCual elige? : ");
	char c = getchar();
	while (getchar() != '\n');
	return (c);
}

//MENU INTRODUCIR STRING
char *fill_string(char *s)
{
	system ("clear");
	printf("String = %s", s);
	printf("\nIntroduzca cadena: \n");
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
	printf("\nIntroduzca num de bytes : \n");
	scanf("%d", &num_bytes);
	getchar();
	return (num_bytes);
}

//MENU PARA INTRODUCIR UN NUM size_t
int	fill_num_sizet()
{
	size_t	num;
	printf("\nIntroduzca num : \n");
	scanf("%zu", &num);
	getchar();
	return (num);
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

//MENU MOSTRAR INTERIOR DE PUNTEROS CHAR O INT CON WRITE
void	output_solucion_ptr(void *ft, void *orig, size_t length)
{
	char	*ft_aux = (char *)ft;
	char	*orig_aux = (char *)orig;
	write(1, "el \\0 sera un #.", 16);

	write(1, "\n\nSolucion_ft__ : ", 18);
	ft_print(ft_aux, length);

	write(1, "\nSolucion_orig : ", 17);
	ft_print(orig_aux, length);
}

//MENU REPETIR
char	repetimos_volvemos()
{
	write(1, "\n\nQuiere probar de nuevo? (y / n) : ", 36);
	char c = getchar();
	while (getchar() != '\n');
	return (c);
}

////////////////////////////////////////////////////////////
/*ft_atoi*//////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_atoi()
{
	char	*s = (char *)calloc(50, sizeof(char));
	char	press;

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
		s = NULL;
	else
		s = fill_string(s);

	//Solucion
	int	solucion_ft = ft_atoi(s);
	int solucion_orig = atoi(s);

	system("clear");
	printf("String: %s", s);
	printf("\n\nft_atoi: %d", solucion_ft);
	printf("\natoi: %d", solucion_orig);
	fflush(stdout); // limpia buffer para write de repetimos
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		s = NULL;
		main_atoi();
		return (0);
	}
	free (s);
	s = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_calloc*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_calloc()
{
	//void *ft_calloc(size_t nmemb, size_t size)
	size_t	nmemb;
	size_t	size;
	char	press;

	system ("clear");
	printf("\nNumero de elementos");
	nmemb = fill_num_sizet();
	printf("\nNumero de Bytes");
	size = fill_num_sizet();

	//asigna en funciones
	char	*ft_ptr_char = (char *)ft_calloc(nmemb, size);
	if (!ft_ptr_char)
		return (-1);
	char	*ptr_char = (char *)calloc(nmemb, size);
	if (!ptr_char)
		return (-1);

	//solucion
	system ("clear");
	output_solucion_ptr(ft_ptr_char, ptr_char, (nmemb * size));
	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		free (ft_ptr_char);
		free (ptr_char);
		main_calloc();
		return (0);
	}
	free (ft_ptr_char);
	free (ptr_char);
	return (0);
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

	char	*solucion_ft = NULL;
	char	*solucion_orig = NULL;

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
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				s2 = fill_string(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				s1 = fill_string(s1);
				break;
			case '3':
				break;
			default:
				break;
		}
	}
	else
	{
		printf("\nS1");
		s1 = fill_string(s1);
		printf("\nS2");
		s2 = fill_string(s2);
	}

	//MENU PARA ELEGIR NUM DE BYTES A BUSCAR
	num_bytes = fill_num_bytes(s1);

	int	solucion_ft = 0;
	int	solucion_orig = 0;

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
/*ft_memcpy*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_memcpy()
{
	//char	*s1 = (char *)calloc(100, sizeof(char));
	//char	*s2 = (char *)calloc(100, sizeof(char));
	char *s1 = NULL;
	char *s2 = NULL;
	char	press;
	int		num_bytes;

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
	 	press = fill_null();
		switch (press){
		case '1':
			s2 = (char *)calloc(100, sizeof(char));
			s2 = fill_string(s2);
			break;
		case '2':
			s1 = (char *)calloc(100, sizeof(char));
			s1 = fill_string(s1);
			break;
		case '3':
			break;
		default:
			break;
	}
	}
	else
	{
		s1 = (char *)calloc(100, sizeof(char));
		s2 = (char *)calloc(100, sizeof(char));
		printf("\nS1");
		s1 = fill_string(s1);
		printf("\nS2");
		s2 = fill_string(s2);
	}

	//MENU PARA ELEGIR NUM DE BYTES A BUSCAR
	num_bytes = fill_num_bytes(s1);

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
					ft_memcpy(s1, s2, num_bytes);
					break;
				case '2':
					memcpy(s1, s2, num_bytes);
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
		ft_memcpy(s1, s2, num_bytes);
		memcpy(s1, s2, num_bytes);
	}

	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nString2 = %s", s2);
	printf("\nbytes = %d", num_bytes);
	fflush(stdout);

	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		if (s1)
			free (s1);
		if (s2)
			free (s2);
		main_memcpy();
		return (0);
	}
	if (s1)
		free (s1);
	if (s2)
		free (s2);
	return (0);
}

////////////////////////////////////////////////////////////
/*ft_memmove*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_memmove()
{
	char *s1 = NULL;
	char *s2 = NULL;
	char *s3 = NULL;// (char *)calloc(100, sizeof(char));
	char *aux1 = (char *)calloc(100, sizeof(char));
	char	press;
	int		num_bytes;
	int		offset;

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
	 	press = fill_null();
		switch (press){
		case '1':
			s2 = (char *)calloc(100, sizeof(char));
			s2 = fill_string(s2);
			break;
		case '2':
			s1 = (char *)calloc(100, sizeof(char));
			s1 = fill_string(s1);
			break;
		case '3':
			break;
		default:
			break;
		}
	}
	else
	{
		s1 = (char *)calloc(100, sizeof(char));
		s2 = (char *)calloc(100, sizeof(char));
		printf("\nS1");
		s1 = fill_string(s1);
		printf("\nS2");
		s2 = fill_string(s2);
	}

	//MENU PARA ELEGIR NUM DE BYTES A BUSCAR
	num_bytes = fill_num_bytes(s1);
	printf("\nIntroduzca offset : \n");
	scanf("%d", &offset);
	getchar(); ////////////////////


	//condiciones NULL
	if ((s1 == NULL) || (s2 == NULL))
	{
		while (1)
		{
			system ("clear");
			printf("String1 = %s", s1);
			printf("\nString2 = %s", s2);
			printf("\nbytes = %d", num_bytes);
			printf("\noffset = %d", offset);

			system("clear");
			printf("\nEl programa puede crashear. Elija la funcion a aplicar y luego repita con la otra para comparar");
			printf("\n\n1. ft_memmove(s1, s2, bytes)");
			printf("\n2. memmove(s1, s2, bytes)");
			printf("\n\n3. ft_memmove(s1, s1 + offset, bytes)");
			printf("\n4. memmove(s1, s1 + offset, bytes)");
			printf("\n\n5. ft_memmove(s1 + offset, s1, bytes)");
			printf("\n\n6. memmove(s1 + offset, s1, bytes)");
			printf("\n\nopcion? : ");
			char press = getchar();
			while (getchar() != '\n');

			switch (press)
			{
				case '1':
					s3 = ft_memmove(s1, s2, num_bytes);
					break;
				case '2':
					s3 = memmove(s1, s2, num_bytes);
					break;
				case '3':
					s3 = ft_memmove(s1, s1 + offset , num_bytes);
					break;
				case '4':
					s3 = memmove(s1, s1 + offset , num_bytes);
					break;
				case '5':
					s3 = ft_memmove(s1 + offset, s1, num_bytes);
					break;
				case '6':
					s3 = memmove(s1 + offset, s1, num_bytes);
					break;
				default:
					continue;
			}
			printf("\nSolucion: %s", s3);
			break;
		}
	}

	//condiciones Normales SOLUCION

	else
	{
		aux1 = strcpy(aux1, s1);

		system ("clear");
		printf("String1 = %s", s1);
		printf("\nString2 = %s", s2);
		printf("\nbytes = %d", num_bytes);
		printf("\noffset = %d", offset);

		s3 = ft_memmove(aux1, s2, num_bytes);
		printf("\n\nft_memmove(s1, s2, bytes): %s", s3);
		aux1 = strcpy(aux1, s1);
		s3 = memmove(aux1, s2, num_bytes);
		printf("\n___memmove(s1, s2, bytes): %s", s3);

		aux1 = strcpy(aux1, s1);
		s3 = ft_memmove(aux1, aux1 + offset, num_bytes);
		printf("\n\nft_memmove(s1, s1 + offset, bytes): %s", s3);
		aux1 = strcpy(aux1, s1);
		s3 = memmove(aux1, aux1 + offset, num_bytes);
		printf("\n___memmove(s1, s1 + offset, bytes): %s", s3);

		aux1 = strcpy(aux1, s1);
		s3 = ft_memmove(aux1 + offset, aux1, num_bytes);
		printf("\n\nft_memmove(s1 + offset, s1, bytes): %s", s3);
		aux1 = strcpy(aux1, s1);
		s3 = memmove(aux1 + offset, aux1, num_bytes);
		printf("\n___memmove(s1 + offset, s1, bytes): %s", s3);
	}


	fflush(stdout);

	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		if (s1) free (s1);
		if (s2) free (s2);
		//if (s3) free (s3);
		if (aux1) free (aux1);
		s1 = NULL;
		s2 = NULL;
		s3 = NULL;
		aux1 = NULL;
		main_memmove();
		return (0);
	}
	if (s1) free (s1);
	if (s2) free (s2);
	//if (s3) free (s3);
	if (aux1) free (aux1);
	s1 = NULL;
	s2 = NULL;
	s3 = NULL;
	aux1 = NULL;
	return (0);
}




////////////////////////////////////////////////////////////
/*ft_memset*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_memset()
{
//void	*ft_memset(void *s, int c, size_t n)

	char	*s1 = (char *)calloc(50, sizeof(char));
	char	press;
	char	c;
	size_t	number;
	int		offset;

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
		s1 = NULL;
	else
	{
		printf("\nS1");
		s1 = fill_string(s1);
	}

	//MENU PARA ELEGIR el CHAR A BUSCAR

	c = fill_char(s1, &offset);

	//MENU PARA ELEGIR NUMERO A INTRODUCIR
	printf("\n numero de bytes: ");
	number = fill_num_bytes(s1);


	char	*solucion_ft = NULL;
	char	*solucion_orig = NULL;


	//condiciones NULL
	if (s1 == NULL)
	{
		while (1)
		{
			system ("clear");
			printf("String1 = %s", s1);
			printf("\nCharacter: %c", c);
			printf("\nbytes = %zu", number);
			press = fill_crash_menu();
			switch (press)
			{
				case '1':
					solucion_ft = ft_memset(s1, (int)c, number);
					break;
				case '2':
					solucion_orig = memset(s1, (int)c, number);
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
		solucion_ft = ft_memset(s1, (int)c, number);
		solucion_orig = memset(s1, (int)c, number);
	}
	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\ncharacter = %c", c);
	printf("\nbytes = %zu", number);
	printf("\n\n Solucion_ft : %s", solucion_ft);
	printf("\n\n Solucion_orig : %s", solucion_orig);
	fflush(stdout);
	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		main_memset();
		return (0);
	}
	free (s1);
	return (0);
}

////////////////////////////////////////////////////////////
/*ft_strdup*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strdup()
{
	//char	*ft_strdup(const char *s)
	char	*s = (char *)calloc(100, sizeof(char));
	char	press;

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
		s = NULL;
	else
		s = fill_string(s);

	char	*solucion_ft = NULL;
	char	*solucion_orig = NULL;

	//condiciones NULL
	if (s == NULL)
	{
		while (1)
		{
			system ("clear");
			printf("String = %s", s);
			press = fill_crash_menu();
			switch (press)
			{
				case '1':
					solucion_ft = ft_strdup(s);
					break;
				case '2':
					solucion_orig = strdup(s);
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
		solucion_ft = ft_strdup(s);
		solucion_orig = strdup(s);
	}

	//SOLUCION
	system ("clear");
	printf("String = %s", s);

	press = output_solution(solucion_ft, solucion_orig);

	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free (solucion_ft);
		free (solucion_orig);
		main_strdup();
		return (0);
	}
	free (s);
	free (solucion_ft);
	free (solucion_orig);
	s = NULL;
	solucion_ft = NULL;
	solucion_orig = NULL;
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

	char	*solucion_ft = NULL;
	char	*solucion_orig = NULL;

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


////////////////////////////////////////////////////////////
/*ft_strjoin*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strjoin()
{
	//char	*ft_strjoin(char const *s1, char const *s2)
	char			*s1 = (char *)calloc(50, sizeof(char));
	char			*s2 = (char *)calloc(50, sizeof(char));
	if (!s1 || !s2)
		return (1);
	char			press;

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				s2 = fill_string(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				s1 = fill_string(s1);
				break;
			case '3':
				break;
			default:
				break;
		}
	}
	else
	{
		system("clear");
		printf("s1: ");
		s1 = fill_string(s1);
		printf("\ns2: ");
		s2 = fill_string(s2);
	}

	char	*solucion_ft = NULL;

	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nString2 = %s", s2);

	solucion_ft = ft_strjoin(s1, s2);

	printf("\n\nJoin: %s", solucion_ft);
	fflush(stdout);
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		free (solucion_ft);
		s1 = NULL;
		s2 = NULL;
		solucion_ft = NULL;
		main_strjoin();
		return (0);
	}
	free (s1);
	free (s2);
	free (solucion_ft);
	s1 = NULL;
	s2 = NULL;
	solucion_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strtrim*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strtrim()
{
	char			*s1 = (char *)calloc(50, sizeof(char));
	char			*s2 = (char *)calloc(50, sizeof(char));
	char			press;

	if (!s1 || !s2)
		return (1);

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				s2 = fill_string(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				s1 = fill_string(s1);
				break;
			case '3':
				break;
			default:
				break;
		}
	}

	else
	{
		system("clear");
		printf("s1: ");
		s1 = fill_string(s1);
		printf("\nset: ");
		s2 = fill_string(s2);
	}

	char	*solucion_ft = NULL;

	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nSET = %s", s2);

	solucion_ft = ft_strtrim(s1, s2);

	printf("\n\nTrim: %s", solucion_ft);
	fflush(stdout);
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		free (solucion_ft);
		s1 = NULL;
		s2 = NULL;
		solucion_ft = NULL;
		main_strtrim();
		return (0);
	}
	free (s1);
	free (s2);
	free (solucion_ft);
	s1 = NULL;
	s2 = NULL;
	solucion_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_substr*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_substr()
{
	//char	*ft_substr(char const *s, unsigned int start, size_t len)
	char			*s = (char *)calloc(100, sizeof(char));
	if (!s)
		return (1);
	unsigned int	num_start;
	size_t			num_len;
	char			press;

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
		s = NULL;
	else
		s = fill_string(s);

	char	*solucion_ft = NULL;

	//ingreso start y len
	system("clear");
	printf("String: %s", s);
	printf("\nStart:");
	num_start = (unsigned int)fill_num_sizet();
	printf("\nLen:");
	num_len = fill_num_sizet();

	//SOLUCION
	system ("clear");
	printf("String = %s", s);
	printf("\nStart: %u", num_start);
	printf("\nLen: %zu", num_len);

	solucion_ft = ft_substr(s, num_start, num_len);
	printf("\n\nCopia: %s", solucion_ft);
	fflush(stdout); //para que write no este antes que el printf por el buffer
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free (solucion_ft);
		main_substr();
		return (0); //si no puede ir al otro free y liberar de nuevo. NO SE COMO. Supongo que por recursividad
	}
	free (s);
	free (solucion_ft);
	s = NULL;
	solucion_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_tolower, ft_toupper*///////////////////////////////////
////////////////////////////////////////////////////////////
int main_uplow(int (*f)(int), int (*g)(int))
{
	//int	ft_toupper(int c)
	char	press;
	char	c1;
	char	c2;
	char	c_orig;
	int		offset = 0;

	//MENU PARA ELEGIR CARACTER
	system ("clear");
	printf("\nOffset para chars como \\0(-49) u Overflow: ");
	scanf("%d", &offset);
	getchar();
	printf("\nIntroduzca el caracter a buscar. \\0 = '1' - 49 : \n");
	scanf("%c", &c1);
	getchar();

	c1= c1 + offset;
	c_orig = c1;
	c2 = c1;

	c1 = f(c1);
	c2 = g(c2);

	//SOLUCION
	system ("clear");
	printf("Char = %c", c_orig);
	printf("\nft_: %c", c1);
	printf("\norig: %c", c2);
	fflush(stdout);

	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
		main_uplow(f, g);
	return (0);
}
