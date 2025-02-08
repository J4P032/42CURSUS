/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:29:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/08 21:20:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h> //tambien system("clear"), malloc...
#include <sys/ioctl.h> //para ioctl. obtener tamanyo de un terminal pantalla.
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <bsd/string.h>
#include "../libft.h"

//PROTOTIPOS funciones print
void	ft_print(char *str, size_t l);
void	ft_printf(char *str);
int		options_draw();
char	options_null_valid();
char 	fill_null();
char	*fill_string(char *s);
int		fill_integer();
int		fill_num_bytes(char *s);
int		fill_num_sizet();
char	fill_char(int *offset);
char	fill_crash_menu();
void	intro_charnulls(char *s);
char	output_solution(char *ft, char *orig);
char	output_solution_int(int *ft, int *orig);
void	output_solucion_ptr(void *ft, void *orig, size_t length);
char	repetimos_volvemos();

//PROTOTIPOS FUNCIONES STRITERI STRMAPI
void ft_strupper(unsigned int index, char *c);
void ft_strlower(unsigned int index, char *c);
void ft_struptolowtoup(unsigned int index, char *c);
void ft_strnext(unsigned int index, char *c);
void ft_strinsertspace(unsigned int index, char *c);
char ft2_strupper(unsigned int index, char c);
char ft2_strlower(unsigned int index, char c);
char ft2_struptolowtoup(unsigned int index, char c);
char ft2_strnext(unsigned int index, char c);
char ft2_strinsertspace(unsigned int index, char c);

//PROTOTIPOS DE FUNCIONES DE LISTAS
void	print_list(t_list *list, char *final);
t_list	*lstpenultimo(t_list *lst);
void	ft_lstadd_before_zero(t_list **lst, t_list *new, char *final);
void	delete_content(void *content);
void	list_upper_lower(void *content);
void	*list_upper_lower2(void *content);

void 	ft_reset_copy(char *dest, char *orig);

//MAIN SECUNDARIAS prototipos
int	main_atoi();
int	main_calloc();
int	main_itoa();
int main_listas();
int	main_memchr();
int	main_memcmp();
int	main_memcpy();
int	main_memmove();
int main_memset();
int main_fd();
int main_split();
int main_strdup();
int	main_strchr(int opcion);
int	main_striteri();
int	main_strjoin();
int main_strlcat();
int main_strlcpy();
int main_strmapi();
int	main_strncmp();
int main_strnstr();
int main_strtrim();
int	main_substr();
int main_uplow(int (*f)(int), int (*g)(int));

////////////////////////////
//EL MAIN GENERAL///////////
////////////////////////////
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
				main_itoa();
				break;
			case '3':
				main_listas();
				break;
			case '4':
				main_memchr();
				break;
			case '5':
				main_memcmp();
				break;
			case '6':
				main_memcpy();
				break;
			case '7':
				main_memmove();
				break;
			case '8':
				main_memset();
				break;
			case '9':
				main_fd();
				break;
			case 'a':
				main_split();
				break;
			case 'b':
				main_strdup();
				break;
			case 'c':
				main_strchr(1);
				break;
			case 'd':
				main_striteri();
				break;
			case 'e':
				main_strjoin();
				break;
			case 'f':
				main_strlcat();
				break;
			case 'g':
				main_strlcpy();
				break;
			case 'h':
				main_strmapi();
				break;
			case 'i':
				main_strncmp();
				break;
			case 'j':
				main_strnstr();
				break;
			case 'k':
				main_strchr(2);
				break;
			case 'l':
				main_strtrim();
				break;
			case 'm':
				main_substr();
				break;
			case 'n':
				main_uplow(ft_tolower, tolower);
				break;
			case 'o':
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
			write(1, "#", 1);
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

//************************//
//MENU DE OPCIONES GENERAL//
//************************//
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
	printf("%5s\n", "(*)nota: imita funciones de C standard");
	printf("%5s\n", "(M)nota: Reserva memoria dentro de la funcion. Danger!");
	printf("%5s\n", "");
	printf("%5s\n", "(0). ft_atoi (*)");
	printf("%5s\n", "(1). ft_calloc (M*)");
	printf("%5s\n", "(2). ft_itoa (M)");

	printf("%5s\n", "(3). ++ft_listas (M->lstnew)");

	printf("%5s\n", "(4). ft_memchr (*)");
	printf("%5s\n", "(5). ft_memcmp (*)");
	printf("%5s\n", "(6). ft_memcpy (*)");
	printf("%5s\n", "(7). ft_memmove (*)");
	printf("%5s\n", "(8). ft_memset (*)");
	printf("%5s\n", "(9). ++ft_PUTS_fd");
	printf("%5s\n", "(a). ft_split (M)");
	printf("%5s\n", "(b). ft_strdup (M*)");
	printf("%5s\n", "(c). ft_strchr (*)");
	printf("%5s\n", "(d). ft_striteri");
	printf("%5s\n", "(e). ft_strjoin (M)");
	printf("%5s\n", "(f). ft_strlcat (*)");
	printf("%5s\n", "(g). ft_strlcpy (*)");

	printf("%5s\n", "(h). ft_strmapi(M)");

	printf("%5s\n", "(i). ft_strncmp (*)");
	printf("%5s\n", "(j). ft_strnstr (*)");
	printf("%5s\n", "(k). ft_strrchr (*)");
	printf("%5s\n", "(l). ft_strtrim (M)");
	printf("%5s\n", "(m). ft_substr (M)");
	printf("%5s\n", "(n). ft_tolower (*)");
	printf("%5s\n", "(o). ft_toupper (*)");
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

//METER \0 EN MEDIO DE UN STRING
void intro_charnulls(char *s)
{
	size_t index = 0;
	size_t longitud = strlen(s);
	repetir:
	system ("clear");


	printf("String = ");
	fflush(stdout);
	ft_print(s, longitud + 1);

	printf("\nQuiere meter nulos en el string?: (s / n)");
	char c = getchar();
	while (getchar() != '\n');
	if ((c == 's') || (c == 'S'))
	{
		printf("\nIntroduzca indice de 0 a %zu : ", longitud - 1);
		scanf("%zu", &index);
		while (getchar() != '\n');
		s[index] = '\0';
		printf("\nQuiere meter mas? (s / n)");
		char c = getchar();
		while (getchar() != '\n');
		if ((c == 's') || (c == 'S'))
			goto repetir;
	}
	else
		system ("clear");
}

//MENU INTRODUCIR STRING
char *fill_string(char *s)
{
	system ("clear");
	printf("String = %s", s);
	printf("\nIntroduzca cadena: \n");
	scanf("%99[^\n]", s); // [^\n]indica que lea todos los caracteres hasta que pulse el espacio
	getchar(); //libera buffer del enter = \n
	return (s);
}

//MENU PARA ELEGIR UN ENTERO
int	fill_integer()
{
	int	num;
	printf("\nIntroduzca el numero : \n");
	scanf("%d", &num);
	getchar();
	return (num);
}

//MENU PARA NUM DE BYTES A RECORRER
int	fill_num_bytes(char *s)
{
	int	num_bytes;
	system ("clear");
	printf("\nString = %s", s);
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
char fill_char(int *offset)
{
	char c;
	system ("clear");
	printf("Introduzca el caracter. Puede alterarlo con el Offset \\0 = '1' - 49(offset) : ");
	scanf("%c", &c);
	getchar();
	printf("\nOffset para chars como \\0(-49) u Overflow: ");
	scanf("%d", offset);
	getchar();
	return (c);
}

//MENU PARA CRASHEOS
char	fill_crash_menu()
{
	printf("\nEl programa puede crashear. Elija la funcion a aplicar y luego repita con la otra para comparar");
	printf("\nNOTA!! en caso de no crash solo fijarse en solucion de la probada y comparar de nuevo con la otra");
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
	printf("\n\nDireccion de memoria de solucion_ft: %p", ft);
	printf("\nDireccion de memoria de solucion_or: %p", orig);

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

//###################################
//FUNCION RESETEAR COPIAR ***********
//###################################
void ft_reset_copy(char *dest, char *orig)
{
	bzero(dest, 100);
	strcpy(dest, orig);
}


////////////////////////////////////////////////////////////
/*ft_atoi*//////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_atoi()
{
	char	*s = NULL;
	char	press;
	int solucion_ft = 0;
	int solucion_orig = 0;

	//INSTRUCCIONES
	system("clear");
	printf("Convierte de un string a un numero entero\n");
	printf("para continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
		s = (char *)calloc(100, sizeof(char));
		s = fill_string(s);
	}

	//condicion NULL
	if (!s)
	{
		while (1)
		{
			system ("clear");
			printf("String1 = %s", s);
			press = fill_crash_menu();
			switch (press)
			{
				case '1':
					solucion_ft = ft_atoi(s);
					break;
				case '2':
					solucion_orig = atoi(s);
					break;
				default:
					continue;
			}
			break;
		}
	}


	//Solucion normal
	else
	{
		solucion_ft = ft_atoi(s);
		solucion_orig = atoi(s);
	}

	system("clear");
	printf("String: %s", s);
	printf("\n\nft_atoi: %d", solucion_ft);
	printf("\natoi___: %d", solucion_orig);
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

	//INSTRUCCIONES
	system("clear");
	printf("Asigna memoria a peticion del numero de elementos y bytes e inicializa a cero\n");
	printf("para continuar presione ENTER\n");
	getchar();


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
/*ft_itoa*//////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_itoa()
{
	char	press;
	int		num;
	char	*solucion_ft = NULL;

	//MENU PARA ELEGIR EL NUM
	system("clear");
	num = fill_integer();

	//SOLUCION

	system ("clear");
	printf("\nNumero = %d", num);

	solucion_ft = ft_itoa(num);

	printf("\n\nft_itoa(%d): %s", num, solucion_ft);

	fflush(stdout);
	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		free(solucion_ft);
		solucion_ft = NULL;
		main_itoa();
		return (0);
	}
	free(solucion_ft);
	solucion_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_listas*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_listas()
{
	char	press = '\0';
	t_list	*test = NULL;
	t_list	*aux = NULL;
	char	*contenido = NULL;
	char	c = 'A';
	//char	final = '?';
	char	*pfinal = NULL;
	size_t	cuantos = 0;
	size_t	num_nodo = 0;
	t_list 	*copy = NULL;

	pfinal = (char *)calloc(1, sizeof(char)); //necesario para hacer no más frees de los necesarios, dentro de la funcion que borra el contenido de ft_lstiter
	*pfinal = '?'; //sangre me ha costado este. Si haciamos un char final = '?', y luego pfinal = &final la cagabamos ya que se perdia la memoria del calloc de pfinal.. Asi no.

	//MENU DE LISTAS
	while (1)
	{
		system("clear");
		printf("%5s", "LISTAS:");
		printf("%5s", "\nNOTA: el caracter ? es el final en un componer normal de la lista a no ser que se ingrese otro nodo al final");
		printf("%5s", "\n");
		printf("%5s", "\n");
		printf("%5s\n", "(1). Componer lista con nuevos nodos(M))");
		printf("%5s\n", "(2). Agregar nodo al FINAL de la lista");
		printf("%5s\n", "(3). Agregar nodo al PRINCIPIO de la lista");
		printf("%5s", "\n");
		printf("%5s\n", "(4). Devolver el ULTIMO nodo de la lista");
		printf("%5s\n", "(5). CUANTOS nodos tiene la lista");
		printf("%5s", "\n");
		printf("%5s\n", "(6). ELIMINA todos los nodos de la lista a partir del elegido");
		printf("%5s\n", "(7). ELIMINA UN nodo de la lista. Cuidado!!!");
		printf("%5s", "\n");
		printf("%5s\n", "(8). Aplica funcion sobre el contenido de todos los nodos a partir del dado");
		printf("%5s\n", "(9). Aplica funcion sobre contido de todos los nodos a partir del dado y devuelve la copia (M)");
		printf("%5s", "\n");
		printf("%5s\n", "(x). Salir");

		printf("\nLista Test: ");
		if (test)
			print_list(test, pfinal);
		if (copy)
		{
			printf("\nLista Copia: ");
			print_list(copy, pfinal);
		}
		if (press == '4')
			printf("\nEl Ultimo nodo de la lista es : %c", *(char *)aux->content);
		if (press == '5')
			printf("\nEl Numero de nodos es de (el ? puede no aparecer en el print) : %zu", cuantos);

		printf("%5s", "\n");
		printf("%5s", "\nQue OPCION quiere? ");


		press = getchar();
		while (getchar() != '\n');
		switch (press)
		{
			case '1':
				contenido = (char *)calloc(1, sizeof(char)); //al hacer un calloc cada vez...
				*contenido = c; //...contenido está en una direccion de memoria diferente y la modificacion de c no le altera.
				aux = ft_lstnew(contenido); //si pasara &c en vez de contenido, todos los ->content de la lista se irían cambiando al nuevo valor de 'c'
				ft_lstadd_before_zero(&test, aux, pfinal); //para no poner A-B- si es el final sino A-B-? ? es el caracter final.
				c++;

				break;
			case '2':
				contenido = (char *)calloc(1, sizeof(char));
				*contenido = c;
				aux = ft_lstnew(contenido);
				ft_lstadd_back(&test, aux);
				c++;
				break;
			case '3':
				contenido = (char *)calloc(1, sizeof(char));
				*contenido = c;
				aux = ft_lstnew(contenido);
				ft_lstadd_front(&test, aux);
				c++;
				break;
			case '4':
				aux = ft_lstlast(test);
				break;
			case '5':
				cuantos = (size_t)ft_lstsize(test);
				break;
			case '6':
				cuantos = ft_lstsize(test);
				system("clear");
				printf("La lista tiene %zu nodos. Elija el nodo a partir del que se eliminaran el y el resto :", cuantos);
				scanf("%zu", &num_nodo);
				getchar();
				if (num_nodo > cuantos || num_nodo == 0) //nodos validos
					break;
				if (num_nodo == 1)
				{
					ft_lstclear(&test, delete_content);
					test = NULL;
				}
				else
				{
					aux = test;
					for (size_t i = 1; i < num_nodo - 1; ++i) //buscamos el nodo elegido pero hasta el anterior para ponerle a NULL (sera el ultimo)
						aux = aux->next;

					t_list *a_borrar = aux->next;
    				aux->next = NULL;  // Cortar la lista aquí
    				ft_lstclear(&a_borrar, delete_content);
				}
				break;
			case '7':
				aux = test;
				cuantos = ft_lstsize(test);
				system("clear");
				printf("La lista tiene %zu nodos. Elija el nodo a borrar (la lista tiene que tener un minimo de 3) :", cuantos);
				scanf("%zu", &num_nodo);
				getchar();
				if (num_nodo > cuantos || cuantos < 3) //nodos validos
					break;
				for (size_t i = 1; i < num_nodo - 1; ++i) //buscamos el nodo elegido pero hasta el anterior para ponerle a NULL (sera el ultimo)
						aux = aux->next;
				t_list *a_borrar = aux->next;
				aux->next = a_borrar->next;
				ft_lstdelone(a_borrar, delete_content);
				break;
			case '8':
				aux = test;
				cuantos = ft_lstsize(test);
				system("clear");
				printf("La lista tiene %zu nodos. Elija el nodo a modificar a partir de :", cuantos);
				scanf("%zu", &num_nodo);
				getchar();
				if (num_nodo > cuantos || num_nodo == 0) //nodos validos
					break;
				for (size_t i = 1; i < num_nodo; ++i)
					aux = aux->next;
				ft_lstiter(aux, list_upper_lower);
				break;
			case '9':
				aux = test;
				cuantos = ft_lstsize(test);
				system("clear");
				printf("La lista tiene %zu nodos. Elija el nodo a modificar a partir de :", cuantos);
				scanf("%zu", &num_nodo);
				getchar();
				if (num_nodo > cuantos || num_nodo == 0) //nodos validos
					break;
				for (size_t i = 1; i < num_nodo; ++i)
					aux = aux->next;
				copy = ft_lstmap(aux, list_upper_lower2, delete_content);
				break;

			case 'X':
			case 'x':
				goto salida;
			default:
				break;
		}
	}


salida:
	fflush(stdout);
	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		ft_lstclear(&test, delete_content);
		test = NULL;
		if (copy)
		{
			ft_lstclear(&copy, delete_content);
			copy = NULL;
		}
		main_listas();
		return (0);
	}
	ft_lstclear(&test, delete_content);
	if (copy)
	{
		ft_lstclear(&copy, delete_content);
		copy = NULL;
	}
	test = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_memchr*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_memchr()
{
	char	*s = NULL;
	char	c;
	int		offset;
	char	press;
	size_t	longitud;
	int		num_bytes;
	char	*s_ft = (char *)calloc(100,sizeof(char));
	char	*s_or = (char *)calloc(100,sizeof(char));
	char	*aux1 = NULL;
	char 	*aux2 = NULL;

	//INSTRUCCIONES
	system("clear");
	printf("Busca el primer byte en donde este el caracter en los primeros n bytes \n");
	printf("Si no lo encuentra devuelve un NULL\n");
	printf("para continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
		s = (char *)calloc(100, sizeof(char));
		s = fill_string(s);
		longitud = strlen(s);

		//INTRODUCIR CARACTERES NULOS EN EL STRING
		if (s)
			intro_charnulls(s);
		memcpy(s_ft, s, longitud + 1);
		memcpy(s_or, s, longitud + 1);
	}
	//MENU PARA ELEGIR NUM DE BYTES A BUSCAR
	num_bytes = fill_num_bytes(s);

	//Menu para elegir char
	c = fill_char(&offset);

	//condiciones NULL
	if (s == NULL)
	{
		while (1)
		{
			system ("clear");
			printf("String = %s", s);
			printf("\nbytes = %d", num_bytes);
			if ((c+offset < 33) || (c+offset > 126))
				printf("\nchar(num) = %d", c + offset);
			else
				printf("\nchar = %c", c + offset);
			press = fill_crash_menu();

			switch (press)
			{
				case '1':
					aux1 = ft_memchr(s, c + offset, num_bytes);
					break;
				case '2':
					aux2 = memchr(s, c + offset, num_bytes);
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
		aux1 = ft_memchr(s_ft, c + offset, num_bytes);
		aux2 = memchr(s_or, c + offset, num_bytes);
	}

	//SOLUCION
	system ("clear");
	ft_print(s, longitud + 1);
	if ((c + offset < 33) || (c + offset > 126))
		printf("\nchar(num) = %d", c + offset);
	else
		printf("\nchar = %c", c + offset);
	printf("\nbytes = %d", num_bytes);

	printf("\n\nDireccion de solucion_ft__: %p\n", aux1);
	printf("Direccion de solucion_orig: %p\n", aux2);

	press = output_solution(aux1, aux2);

	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free (s_ft);
		free (s_or);
		main_memchr();
		return (0);
	}
	free (s);
	free(s_ft);
	free(s_or);
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_memcmp*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_memcmp()
{
	char	*s1 = NULL;
	char	*s2 = NULL;
	char	press;
	int		num_bytes;

	//INSTRUCCIONES
	system("clear");
	printf("Compara dos posiciones de memoria hasta los n bytes\n");
	printf("Devuelve 0 si son iguales o la diferencia en ascii en el\n");
	printf("primer byte que sea diferente. Con n = 0 devuelve 0\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	//CASOS NULL
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
	//CASOS NORMALES
	else
	{
		printf("\nS1");
		s1 = (char *)calloc(100, sizeof(char));
		s1 = fill_string(s1);
		printf("\nS2");
		s2 = (char *)calloc(100, sizeof(char));
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
	char *s1 = NULL;
	char *s2 = NULL;
	char *s_ft = (char *)malloc(100);
	char *s_or = (char *)malloc(100);
	char	press;
	int		num_bytes;
	size_t	longitud;


	//INSTRUCCIONES
	system("clear");
	printf("Copia n bytes de la memoria origen a la destino.\n");
	printf("No deben solaparse\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

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

	if (s2)
		longitud = strlen(s2);
	system("clear");
	if (s2)
		intro_charnulls(s2);

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
					if (s1)
						strcpy(s_ft, s1);
					ft_memcpy(s_ft, s2, num_bytes);
					break;
				case '2':
					if (s1)
						strcpy(s_or, s1);
					memcpy(s_or, s2, num_bytes);
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
		strcpy(s_ft, s1);
		ft_memcpy(s_ft, s2, (size_t)num_bytes);
		strcpy(s_or, s1);
		memcpy(s_or, s2, (size_t)num_bytes);
	}

	//SOLUCION
	system ("clear");
	printf("String1 = ");
	fflush(stdout);
	ft_print(s2, longitud + 1);
	printf("\nString2 = %s", s2);
	printf("\nbytes = %d", num_bytes);
	printf("\n\nSolucion_ft: ");
	fflush(stdout);
	ft_print(s_ft, longitud + 1);
	printf("\n\nSolucion_Or: ");
	fflush(stdout);
	ft_print(s_or, longitud + 1);

	printf("\n\nDireccion de solucion_ft__: %p\n", s_ft);
	printf("Direccion de solucion_orig: %p\n", s_or);


	fflush(stdout);

	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		if (s1)
			free (s1);
		if (s2)
			free (s2);
		if (s_ft)
			free (s_ft);
		if (s_or)
			free (s_or);
		s1 = NULL;
		s2 = NULL;
		s_ft = NULL;
		s_or = NULL;
		main_memcpy();
		return (0);
	}
		if (s1)
			free (s1);
		if (s2)
			free (s2);
		if (s_ft)
			free (s_ft);
		if (s_or)
			free (s_or);
		s1 = NULL;
		s2 = NULL;
		s_ft = NULL;
		s_or = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_memmove*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_memmove()
{
	char *s1 = NULL;
	char *s2 = NULL;
	char *s_ft = (char *)calloc(100, sizeof(char));
	char *s_or = (char *)calloc(100, sizeof(char));
	char	press;
	int		num_bytes;
	int		offset;

	//INSTRUCCIONES
	system("clear");
	printf("Copia datos del origen al destino en n bytes pero garantiza una buena copia\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

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
	getchar();


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

			printf("\n\nEl programa puede crashear. Elija la funcion a aplicar y luego repita con la otra para comparar");
			printf("\n\n1. ft_memmove(s1, s2, bytes)");
			printf("\n2. memmove(s1, s2, bytes)");
			printf("\n\n3. ft_memmove(s1, s1 + offset, bytes)");
			printf("\n4. memmove(s1, s1 + offset, bytes)");
			printf("\n\n5. ft_memmove(s1 + offset, s1, bytes)");
			printf("\n6. memmove(s1 + offset, s1, bytes)");
			printf("\n\nopcion? : ");
			char press = getchar();
			while (getchar() != '\n');

			switch (press)
			{
				case '1':
					strcpy(s_ft, s1);
					ft_memmove(s_ft, s2, num_bytes);
					break;
				case '2':
					strcpy(s_or, s1);
					memmove(s_or, s2, num_bytes);
					break;
				case '3':
					strcpy(s_ft, s1);
					ft_memmove(s_ft, s_ft + offset , num_bytes);
					break;
				case '4':
					strcpy(s_or, s1);
					memmove(s_or, s_or + offset , num_bytes);
					break;
				case '5':
					strcpy(s_ft, s1);
					ft_memmove(s_ft + offset, s_ft, num_bytes);
					break;
				case '6':
					strcpy(s_or, s1);
					memmove(s_or + offset, s_or, num_bytes);
					break;
				default:
					continue;
			}
			printf("\nSolucion_ft: %s", s_ft);
			printf("\nSolucion_or: %s", s_or);
			break;
		}
	}

	//condiciones Normales SOLUCION

	else
	{
		strcpy(s_ft, s1);
		strcpy(s_or, s1);

		system ("clear");
		printf("String1 = %s", s1);
		printf("\nString2 = %s", s2);
		printf("\nbytes = %d", num_bytes);
		printf("\noffset = %d", offset);

		ft_memmove(s_ft, s2, num_bytes);
		printf("\n\nft_memmove(s1, s2, bytes): %s", s_ft);
		memmove(s_or, s2, num_bytes);
		printf("\n___memmove(s1, s2, bytes): %s", s_or);

		printf("\nDireccion de solucion_ft__: %p\n", s_ft);
		printf("Direccion de solucion_orig: %p\n", s_or);

		ft_reset_copy(s_ft, s1);
		ft_memmove(s_ft, s_ft + offset, num_bytes);
		printf("\n\nft_memmove(s1, s1 + offset, bytes): %s", s_ft);
		ft_reset_copy(s_or, s1);
		memmove(s_or, s_or + offset, num_bytes);
		printf("\n___memmove(s1, s1 + offset, bytes): %s", s_or);

		printf("\nDireccion de solucion_ft__: %p\n", s_ft);
		printf("Direccion de solucion_orig: %p\n", s_or);

		ft_reset_copy(s_ft, s1);
		ft_memmove(s_ft + offset, s_ft, num_bytes);
		printf("\n\nft_memmove(s1 + offset, s1, bytes): %s", s_ft);
		ft_reset_copy(s_or, s1);
		memmove(s_or + offset, s_or, num_bytes);
		printf("\n___memmove(s1 + offset, s1, bytes): %s", s_or);

		printf("\nDireccion de solucion_ft__: %p\n", s_ft);
		printf("Direccion de solucion_orig: %p\n", s_or);
	}


	fflush(stdout);

	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		if (s1) free (s1);
		if (s2) free (s2);
		if (s_or) free (s_or);
		if (s_ft) free (s_ft);
		s1 = NULL;
		s2 = NULL;
		s_ft = NULL;
		s_or = NULL;
		main_memmove();
		return (0);
	}
	if (s1) free (s1);
	if (s2) free (s2);
	if (s_or) free (s_or);
	if (s_ft) free (s_ft);
	s1 = NULL;
	s2 = NULL;
	s_ft = NULL;
	s_or = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_memset*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_memset()
{

	char	*s1 = NULL;
	char	*s_ft = (char *)calloc(100,sizeof(char));
	char	*s_or = (char *)calloc(100,sizeof(char));
	char	press;
	char	c;
	size_t	number;
	int		offset;

	//INSTRUCCIONES
	system("clear");
	printf("Rellena los primeros n bytes de memoria del string con el character elegido\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
		printf("\nS1");
		s1 = (char *)calloc(100, sizeof(char));
		s1 = fill_string(s1);
	}

	//MENU PARA ELEGIR el CHAR A BUSCAR

	c = fill_char(&offset);

	//MENU PARA ELEGIR NUMERO A INTRODUCIR
	number = fill_num_bytes(s1);

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
			strcpy(s_ft, s1);
			strcpy(s_or, s1);
			switch (press)
			{
				case '1':
					ft_memset(s_ft, (int)c + offset, number);
					break;
				case '2':
					memset(s_or, (int)c + offset, number);
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
		strcpy(s_ft, s1);
		ft_memset(s_ft, (int)c + offset, number);
		strcpy(s_or,s1);
		memset(s_or, (int)c + offset, number);
	}
	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\ncharacter = %c", c + offset);
	printf("\nbytes = %zu", number);
	printf("\n\n Solucion_ft : %s", s_ft);
	printf("\n\n Solucion_or : %s", s_or);

	printf("\n\nDireccion de memoria de solucion_ft: %p", s_ft);
	printf("\nDireccion de memoria de solucion_ft: %p", s_or);

	fflush(stdout);
	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		if (s1)
			free (s1);
		if (s_ft)
			free (s_ft);
		if (s_or)
			free (s_or);
		s1 = NULL;
		s_ft = NULL;
		s_or  = NULL;
		main_memset();
		return (0);
	}
	if (s1)
		free (s1);
	if (s_ft)
		free (s_ft);
	if (s_or)
		free (s_or);
	s1 = NULL;
	s_ft = NULL;
	s_or  = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_fd*////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_fd()
{

	char	*s = NULL;
	char	press;
	char	c;
	int		offset;
	int		fd;
	int		number;

	//INSTRUCCIONES
	system("clear");
	printf("ft_putchar_fd: Manda por el file descriptor el caracter c que elijamos con  write\n");
	printf("ft_putendl_fd: Escribe con write el string mandado y le añade un salto de linea al final por el fd\n");
	printf("ft_putnbr_fd: Escribe el numero en enteros con write por el fd mandado\n");
	printf("ft_str_fd: Escribe con write el string mandado y lo suelta por el fd elegido\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
		printf("\ns");
		{
			s = (char *)calloc(100, sizeof(char));
			s = fill_string(s);
		}
	}

	//MENU PARA ELEGIR el CHAR A BUSCAR
	c = fill_char(&offset);

	//MENU PARA ELEGIR EL FD FILE DESCRIPTOR
	printf("\nFile Descriptor (FD)");
	fd = fill_integer();

	//MENU PARA ELEGIR NUMERO A INTRODUCIR
	printf("\nNumero para ser pasado a ft_putnbr_fd");
	number = fill_integer();

	//condiciones NULL
	if (s == NULL)
	{
		while (1)
		{
			system ("clear");

			int fd_forzado = open("/dev/tty", O_WRONLY);
			if (fd_forzado == -1)
			{
				perror("\nError al generar el fd");
				return (1);
			}
			dup2(fd_forzado, fd);
			printf("String = %s", s);
			printf("\nCharacter : %c", c + offset);
			printf("\nEl descriptor fd abierto es : %d", fd_forzado);
			printf("\nEl fd ha cambiado al : %d", fd);
			printf("\nEl Numero pasado es: %d", number);
			fflush(stdout);

			write(1, "\n\nft_putchar_fd : ", 18);
			ft_putchar_fd(c + offset, fd);

			write(1, "\nft_putnbr_fd : ", 16);
			ft_putnbr_fd(number, fd);

			printf("\nPresione ENTER para continuar (puede crashear)");
			getchar();
			fflush(stdout);
			write(1, "\nft_putendl_fd : ", 17);
			ft_putendl_fd(s, fd);


			printf("\nPresione ENTER para continuar (puede crashear)");
			getchar();
			fflush(stdout);
			write(1, "\nft_putstr_fd : ", 16);
			ft_putstr_fd(s, fd);

			close(fd_forzado);
			break;
		}
	}
	//condiciones Normales
	else
	{
		system ("clear");
		//fd = open ("solucion.txt", O_CREAT | O_WRONLY, 0644); //permisos: 0(octal)6=4+2->lee y escribe...(propietario)4(grupo)4(otros). //cada numero significa 0=sinpermiso 1=ejecutar 2=escribir 4=leer
		int fd_forzado = open("/dev/tty", O_WRONLY);
		if (fd_forzado == -1)
		{
			perror("\nError al generar el fd");
			return (1);
		}
		//cambia el generado por el fd elegido
		dup2(fd_forzado, fd);

		printf("String = %s", s);
		printf("\nCharacter pasado por fd: %c", c + offset);
		printf("\nEl descriptor fd abierto es : %d", fd_forzado);
		printf("\nEl fd ha cambiado al : %d", fd);
		printf("\nEl Numero pasado es: %d", number);
		fflush(stdout);

		write(1, "\n\nft_putchar_fd : ", 18);
		ft_putchar_fd(c + offset, fd);

		write(1, "\nft_putnbr_fd : ", 16);
		ft_putnbr_fd(number, fd);

		write(1, "\nft_putendl_fd : ", 17);
		ft_putendl_fd(s, fd);

		write(1, "\nft_putstr_fd : ", 16);
		ft_putstr_fd(s, fd);

		close(fd_forzado);
	}

	fflush(stdout);

	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		if (s)
			free(s);
		s = NULL;
		main_fd();
		return (0);
	}
	if (s)
		free(s);
	s = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_split*/////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_split()
{
	char *s1 = NULL;
	char	**solucion = NULL;
	char	press;
	char	c;
	int		offset = 0;
	size_t	i = 0;


	//INSTRUCCIONES
	system("clear");
	printf("separa un string en un array de strings a partir de un caracter separador definido\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
	 	s1 = (char *)calloc(100, sizeof(char));
		if (!s1) exit(1);
		printf("\nString");
		s1 = fill_string(s1);
	}

	//MENU PARA ELEGIR Caracter Separador
	c = fill_char(&offset);

	//condiciones NULL
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nSeparador = %c", c + offset);

	if (s1 == NULL)
	{
		printf("\nVa a salir la solución pero el programa puede crashear");
		printf("\nPresiona la tecla ENTER para continuar");
		getchar();
		solucion = ft_split(s1, c);
	}
	//condiciones Normales
	else
		solucion = ft_split(s1, c);

	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nSeparador = %c", c + offset);
	printf("\n\nSolucion_ft: \n");
	while (solucion[i])
	{
		printf("solucion[%zu] : %s\n", i, solucion[i]);
		i++;
	}

	fflush(stdout);

	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		i = 0;
		free(s1);
		s1 = NULL;
		while (solucion[i])
		{
			free(solucion[i]);
			solucion[i] = NULL;
			i++;
		}
		if (solucion)
			free (solucion);
		solucion = NULL;
		main_split();

		return (0);
	}
	i = 0;
	free(s1);
	s1 = NULL;
	while (solucion[i])
	{
		free(solucion[i]);
		solucion[i] = NULL;
		i++;
	}
	if (solucion)
		free (solucion);
	solucion = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strdup*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strdup()
{

	char	*s = NULL;
	char	*s_ft = (char *)calloc(100, sizeof(char));
	if (!s_ft) exit(1);
	char	*s_or = (char *)calloc(100, sizeof(char));
	if (!s_or) exit(1);
	char	press;
	size_t	longitud;

	//INSTRUCCIONES
	system("clear");
	printf("copia un string en otra area de memoria. A NULL will return NULL\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();


	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
		s = (char *)calloc(100, sizeof(char));
		if (!s) exit(1);
		s = fill_string(s);
		longitud = strlen(s);
		//INTRODUCIR CARACTERES NULOS EN EL STRING
		if (s)
			intro_charnulls(s);

		memcpy(s_ft, s, longitud + 1);
		memcpy(s_or, s, longitud + 1);
	}

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
					solucion_ft = ft_strdup(s_ft);
					break;
				case '2':
					solucion_orig = strdup(s_or);
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
		solucion_ft = ft_strdup(s_ft);
		solucion_orig = strdup(s_or);
	}

	//SOLUCION
	system ("clear");
	ft_print(s, longitud + 1);

	printf("\nSolucion_Ft: ");
	fflush(stdout);
	ft_print(solucion_ft, longitud);
	printf("\nSolucion_Orig: ");
	fflush(stdout);
	ft_print(solucion_orig, longitud);

	printf("\nDireccion de memoria de ft__: %p", solucion_ft);
	printf("\nDireccion de memoria de orig: %p", solucion_orig);
	fflush(stdout);

	press = repetimos_volvemos();

	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free (s_ft);
		free (s_or);
		free (solucion_ft);
		free (solucion_orig);
		s = NULL;
		s_ft = NULL;
		s_or = NULL;
		solucion_ft = NULL;
		solucion_orig = NULL;
		main_strdup();
		return (0);
	}
	free (s);
	free (s_ft);
	free (s_or);
	free (solucion_ft);
	free (solucion_orig);
	s = NULL;
	s_ft = NULL;
	s_or = NULL;
	solucion_ft = NULL;
	solucion_orig = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strchr ft_strrchr*/////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strchr(int opcion)
{
	char	*s = NULL;
	char	c;
	int		offset = 0;
	char	press;
	char	*s_ft = (char *)calloc(100, sizeof(char));
	if (!s_ft) exit(1);
	char	*s_or = (char *)calloc(100, sizeof(char));
	if (!s_or) exit(1);
	int		longitud = 0;

	//INSTRUCCIONES
	system("clear");
	if (opcion == 1)
	{
		printf("Encuentra un caracter c dentro de un string. Si lo encuentra devuelve posicion del primero encontrado\n");
		printf("Si no devolverá un NULL, Si es el \\0 devolvera el primer terminador\n");
	}
	else
	{
		printf("Encuentra un caracter c dentro de un string. Pero este devuelve la ultima posición de dicho char\n");
		printf("Si no devolverá un NULL, Si es el \\0 devolvera el primer terminador\n");
	}
		printf("\nPara continuar presione ENTER\n");
		getchar();


	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
		s = (char *)calloc(100, sizeof(char));
		if (!s) exit(1);
		s = fill_string(s);
		longitud = strlen(s);
	}

	//INTRODUCIR CARACTERES NULOS EN EL STRING
	if (s)
		intro_charnulls(s);

	if (s)
	{
		memcpy(s_ft, s, longitud + 1);
		memcpy(s_or, s, longitud + 1);
	}

	//Menu para elegir char
	c = fill_char(&offset);

	char	*solucion_ft = NULL;
	char	*solucion_orig = NULL;

	//condiciones NULL
	if (s == NULL)
	{

		while (1)
		{
			system ("clear");
			printf("String = %s", s);
			if ((c+offset < 33) || (c+offset > 126)) //no print
				printf("\nchar(num) = %d", c + offset); //char en int
			else
				printf("\nchar = %c", c + offset);
			press = fill_crash_menu();

			switch (press)
			{
				case '1':
					if (opcion == 1)
						solucion_ft = ft_strchr(s_ft,c + offset);
					else if (opcion == 2)
						solucion_ft = ft_strrchr(s_ft,c + offset);
					break;
				case '2':
					if (opcion == 1)
						solucion_orig = strchr(s_ft,c + offset);
					else if (opcion == 2)
						solucion_orig = strrchr(s_ft,c + offset);
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
			solucion_ft = ft_strchr(s_ft,c + offset); //+offset por que si no es convertida y no vale la prueba
			solucion_orig = strchr(s_or,c + offset);
		}
		if (opcion == 2)
		{
			solucion_ft = ft_strrchr(s_ft,c + offset);
			solucion_orig = strrchr(s_or,c + offset);
		}
	}

	//SOLUCION
	system ("clear");
	ft_print(s, longitud + 1);
	if ((c+offset < 33) || (c+offset > 126)) //no print
		printf("\nchar(num) = %d", c + offset); //char en int
	else
		printf("\nchar = %c", c + offset);

	press = output_solution(solucion_ft, solucion_orig);


	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free(s_or);
		free(s_ft);
		s = NULL; //proteccion frente a doble free
		s_or = NULL;
		s_ft = NULL;
		if (opcion == 1)
			main_strchr(1);
		else if (opcion == 2)
			main_strchr(2);
		return (0); //si no puede ir al otro free y liberar de nuevo. NO SE COMO. Supongo que por recursividad
	}
	free (s);
	free(s_or);
	free(s_ft);
	s = NULL; //proteccion frente a doble free
	s_or = NULL;
	s_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_striteri*//////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_striteri()
{
	char	*s = NULL;
	char	press;

	//INSTRUCCIONES
	system("clear");
	printf("Pasa el string creado por la funcion que elijamos");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	//Opciones normales
	if (press == '2')
	{
		system("clear");
		s = (char *)calloc(100, sizeof(char));
		if (!s) exit(1);
		s = fill_string(s);
	}
	char	*solucion = (char *)calloc(100, sizeof(char));
	strcpy(solucion, s);

	//MENU ELECCION FUNCION

	system ("clear");
	printf("String: %s",s);

	ft_striteri(solucion, ft_strupper);
	printf("\n\nft_striteri Mayusculas todo : %s", solucion);
	ft_reset_copy(solucion, s);

	ft_striteri(solucion, ft_strlower);
	printf("\nft_striteri Minusculas todo : %s", solucion);
	ft_reset_copy(solucion, s);

	ft_striteri(solucion, ft_struptolowtoup);
	printf("\nft_striteri alterna May-Min : %s", solucion);
	ft_reset_copy(solucion, s);

	ft_striteri(solucion, ft_strnext);
	printf("\nft_striteri sugiente char en ascii : %s", solucion);
	ft_reset_copy(solucion, s);

	ft_striteri(solucion, ft_strinsertspace);
	printf("\nft_striteri inserta un * en los chars impares : %s", solucion);


	fflush(stdout);
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free (solucion);
		s = NULL;
		solucion = NULL;
		main_striteri();
		return (0);
	}
	free (s);
	free (solucion);
	s = NULL;
	solucion = NULL;

	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strjoin*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strjoin()
{
	char	*s1 = NULL;
	char	*s2 = NULL;
	size_t	lon1 = 0;
	size_t	lon2 = 0;

	char	press;

	//INSTRUCCIONES
	system("clear");
	printf("\nJunta dos strings en uno en una nueva direccion de memoria");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				if (!s2) exit(1);
				s2 = fill_string(s2);
				lon2 = strlen(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				if (!s1) exit(1);
				s1 = fill_string(s1);
				lon1 = strlen(s1);
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
		s1 = (char *)calloc(100, sizeof(char));
		if (!s1) exit(1);
		s1 = fill_string(s1);
		if (s1)
			lon1 = strlen(s1);
		if (s1)
			intro_charnulls(s1);

		printf("\ns2: ");
		s2 = (char *)calloc(100, sizeof(char));
		if (!s2) exit(1);
		s2 = fill_string(s2);
		if (s2)
			lon2 = strlen(s2);
		if (s2)
			intro_charnulls(s2);
	}

	char	*solucion_ft = NULL;

	//SOLUCION
	system ("clear");
	printf("String1 = ");
	fflush(stdout);
	ft_print(s1, lon1 + 1);
	printf("\nString2 = ");
	fflush(stdout);
	ft_print(s2, lon2 + 1);

	solucion_ft = ft_strjoin(s1, s2);

	printf("\n\nJoin: ");
	fflush(stdout);
	ft_print(solucion_ft, lon1 + lon2 + 1);

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
/*ft_strlcat*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strlcat()
{
	char	*s1 = NULL;
	char	*s2 = NULL;
	size_t	size = 0;

	//size_t	lon1 = 0;

	char	press;


	//INSTRUCCIONES
	system("clear");
	printf("Concatena el string s2 detras de s1 hasta un tamaño marcado y que incluye el terminador \\0");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				if (!s2) exit(1);
				s2 = fill_string(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				if (!s1) exit(1);
				s1 = fill_string(s1);
				//lon1 = strlen(s1);
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
		printf("destino: ");
		s1 = (char *)calloc(100, sizeof(char));
		if (!s1) exit(1);
		s1 = fill_string(s1);
		//lon1 = strlen(s1);

		printf("\norigen: ");
		s2 = (char *)calloc(100, sizeof(char));
		if (!s2) exit(1);
		s2 = fill_string(s2);
	}


	//MENU PARA ELEGIR NUMERO A INTRODUCIR
	printf("longitud: ");
	size = (int)fill_integer();

	char	*s_ft = (char *)calloc(100, sizeof(char));
	if (!s_ft) exit(1);
	char	*s_or = (char *)calloc(100, sizeof(char));
	if (!s_or) exit(1);

	strcpy(s_ft, s1);
	strcpy(s_or, s1);

	size_t solucion_ft = 0;
	size_t solucion_or = 0;

	//SOLUCION
	system ("clear");
	printf("Destino = %s", s1);
	printf("\nOrigen = %s", s2);
	printf("\nLongitud : %zu", size);

	solucion_ft = ft_strlcat(s_ft, s2, size);
	solucion_or = strlcat(s_or, s2, size);

	printf("\n\nft_strlcat: %s",s_ft);
	printf("\n___strlcat: %s", s_or);
	printf("\nsolucion_ft: %zu", solucion_ft);
	printf("\nsolucion_or: %zu", solucion_or);

	printf("\n\nDireccion _____Origen: %p", s2);
	printf("\nDireccion Destino ft_: %p", s_ft);
	printf("\nDireccion Destino Ori: %p", s_or);

	fflush(stdout);

	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		free (s_ft);
		free (s_or);
		s1 = NULL;
		s2 = NULL;
		s_or = NULL;
		s_ft = NULL;
		main_strlcat();
		return (0);
	}
	free (s1);
	free (s2);
	free (s_ft);
	free (s_or);
	s1 = NULL;
	s2 = NULL;
	s_or = NULL;
	s_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strlcpy*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strlcpy()
{

	char	*s1 = NULL;
	char	*s2 = NULL;
	size_t	size = 0;

	size_t	lon1 = 0;
	size_t	lon2 = 0;
	char	*s_ft = (char *)calloc(100, sizeof(char));
	if (!s_ft) exit(1);
	char	*s_or = (char *)calloc(100, sizeof(char));
	if (!s_or) exit(1);

	char	press;


	//INSTRUCCIONES
	system("clear");
	printf("Copia el string hasta el tamanyo seleccionado y devuelve la longitud de el string origen");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				if (!s2) exit(1);
				s2 = fill_string(s2);
				lon2 = strlen(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				if (!s1) exit(1);
				s1 = fill_string(s1);
				lon1 = strlen(s1);
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
		printf("Destino: ");
		s1 = (char *)calloc(100, sizeof(char));
		if (!s1) exit(1);
		s1 = fill_string(s1);
		lon1 = strlen(s1);

		printf("\nOrigen: ");
		s2 = (char *)calloc(100, sizeof(char));
		if (!s2) exit(1);
		s2 = fill_string(s2);
		lon2 = strlen(s2);
	}


	//MENU PARA ELEGIR NUMERO A INTRODUCIR
	printf("Longitud: ");
	size = (int)fill_integer();

	strcpy(s_ft, s1);
	strcpy(s_or, s1);

	size_t solucion_ft = 0;
	size_t solucion_or = 0;


	//SOLUCION
	system ("clear");
	printf("Destino = ");
	fflush(stdout);
	ft_print(s1, lon1 + 1);
	printf("\nOrigen = ");
	fflush(stdout);
	ft_print(s2, lon2 + 1);
	printf("\nLongitud : %zu", size);

	solucion_ft = ft_strlcpy(s_ft, s2, size);
	solucion_or = strlcpy(s_or, s2, size);

	printf("\n\nft_strlcpy: %s", s_ft);
	printf("\n___strlcpy: %s", s_or);

	printf("\nsolucion_ft: %zu", solucion_ft);
	printf("\nsolucion_or: %zu", solucion_or);

	printf("\n\nDireccion _____Origen: %p", s2);
	printf("\nDireccion Destino ft_: %p", s_ft);
	printf("\nDireccion Destino ori: %p", s_or);

	fflush(stdout);

	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		free (s_ft);
		free (s_or);
		s1 = NULL;
		s2 = NULL;
		s_or = NULL;
		s_ft = NULL;
		main_strlcpy();
		return (0);
	}
	free (s1);
	free (s2);
	free (s_ft);
	free (s_or);
	s1 = NULL;
	s2 = NULL;
	s_or = NULL;
	s_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strmapi*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strmapi()
{
	char	*s = NULL;
	char	press;

	//INSTRUCCIONES
	system("clear");
	printf("Pasa el string creado por la funcion que elijamos pasando una copia");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	//Opciones normales
	if (press == '2')
	{
		system("clear");
		s = (char *)calloc(100, sizeof(char));
		if (!s) exit(1);
		s = fill_string(s);
	}
	char	*solucion = NULL;


	//MENU ELECCION FUNCION

	system ("clear");
	printf("String: %s",s);

	solucion = ft_strmapi(s, ft2_strupper);
	printf("\n\nft_strmapi Mayusculas todo : %s", solucion);
	free(solucion);
	solucion = NULL;

	solucion = ft_strmapi(s, ft2_strlower);
	printf("\nft_strmapi Minusculas todo : %s", solucion);
	free(solucion);
	solucion = NULL;

	solucion = ft_strmapi(s, ft2_struptolowtoup);
	printf("\nft_strmapi alterna May-Min : %s", solucion);
	free(solucion);
	solucion = NULL;

	solucion = ft_strmapi(s, ft2_strnext);
	printf("\nft_strmapi sugiente char en ascii : %s", solucion);
	free(solucion);
	solucion = NULL;

	solucion = ft_strmapi(s, ft2_strinsertspace);
	printf("\nft_strmapi inserta un * en los chars impares : %s", solucion);


	fflush(stdout);
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free (solucion);
		s = NULL;
		solucion = NULL;
		main_striteri();
		return (0);
	}
	free (s);
	free (solucion);
	s = NULL;
	solucion = NULL;
	return (0);

}


////////////////////////////////////////////////////////////
/*ft_strncmp*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strncmp()
{
	char	*s1 = NULL;
	char	*s2 = NULL;
	size_t	size = 0;

	char	press;

	//INSTRUCCIONES
	system("clear");
	printf("Compara los dos strings pasados y devuelve su diferencia. Si son iguales, devuelve un cero\n");
	printf("Si no lo son devuelve la resta entre el primer caracter no igual s1 - s2\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				if (!s2) exit(1);
				s2 = fill_string(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				if (!s1) exit(1);
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
		printf("String1: ");
		s1 = (char *)calloc(100, sizeof(char));
		if (!s1) exit(1);
		s1 = fill_string(s1);

		printf("\nString2: ");
		s2 = (char *)calloc(100, sizeof(char));
		if (!s2) exit(1);
		s2 = fill_string(s2);
	}


	//MENU PARA ELEGIR NUMERO A INTRODUCIR
	printf("Longitud a buscar: ");
	size = (int)fill_integer();

	int solucion_ft = 0;
	int solucion_or = 0;

	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nString2 = %s", s2);
	printf("\nLongitud : %zu", size);

	solucion_ft = ft_strncmp(s1, s2, size);
	solucion_or = strncmp(s1, s2, size);

	printf("\n\nft_strncmp: %d", solucion_ft);
	printf("\n___strncmp: %d", solucion_or);

	if (solucion_or == 0)
		printf("\nLas dos cadenas son iguales hasta el char %zu", size);
	else if (solucion_or < 0)
		printf("\nLa cadena \"%s\" es mas grande que la cadena \"%s\" hasta el char %zu", s2, s1, size);
	else if (solucion_or > 0)
		printf("\nLa cadena \"%s\" es mas pequeña que la cadena \"%s\" hasta el char %zu", s2, s1, size);

	fflush(stdout);

	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		s1 = NULL;
		s2 = NULL;
		main_strncmp();
		return (0);
	}
	free (s1);
	free (s2);
	s1 = NULL;
	s2 = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strnstr*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strnstr()
{
	char	*s1 = NULL;
	char	*s2 = NULL;

	size_t	lon1 = 0;
	size_t	lon2 = 0;
	char	*s_ft = (char *)calloc(100, sizeof(char));
	if (!s_ft) exit(1);
	char	*s_or = (char *)calloc(100, sizeof(char));
	if (!s_or) exit(1);

	size_t	size = 0;

	char	press;

	//INSTRUCCIONES
	system("clear");
	printf("Busca la cadena little en big hasta la longitud deseada Si lo encuentra devuelve la posicion a la primera coincidencia\n");
	printf(". Si little es una cadena vacia devuelve big. Si no devuelve NULL\n");
	printf("\nPara continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				if (!s2) exit(1);
				s2 = fill_string(s2);
				if (s2)
					lon2 = strlen(s2);
				if (s2)
					intro_charnulls(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				if (!s1) exit(1);
				s1 = fill_string(s1);
				lon1 = strlen(s1);
				memcpy(s_ft, s1, lon1 + 1);
				memcpy(s_or, s1, lon1 + 1);
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
		printf("Big: ");
		s1 = (char *)calloc(100, sizeof(char));
		if (!s1) exit(1);
		s1 = fill_string(s1);
		lon1 = strlen(s1);
		memcpy(s_ft, s1, lon1 + 1);
		memcpy(s_or, s1, lon1 + 1);

		printf("\nLittle: ");
		s2 = (char *)calloc(100, sizeof(char));
		if (!s2) exit(1);
		s2 = fill_string(s2);
		if (s2)
		{
			lon2 = strlen(s2);
			intro_charnulls(s2);
		}
	}


	//MENU PARA ELEGIR NUMERO A INTRODUCIR
	printf("Longitud a buscar: ");
	size = (int)fill_integer();

	//SOLUCION
	system ("clear");
	printf("Big = %s", s1);
	printf("\nLittle = ");
	fflush(stdout);
	if (s2)
		ft_print(s2,lon2 + 1);
	printf("\nLongitud : %zu", size);

	char	*solucion_ft = NULL;
	char	*solucion_or = NULL;

	solucion_ft = ft_strnstr(s_ft, s2, size);
	solucion_or = strnstr(s_or, s2, size);

	printf("\n\nft_strnstr: %s", solucion_ft);
	printf("\n___strncmp: %s", solucion_or);

	printf("\nDireccion Destino ft_: %p", solucion_ft);
	printf("\nDireccion Destino ori: %p", solucion_or);

	fflush(stdout);

	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		free (s_ft);
		free (s_or);
		s1 = NULL;
		s2 = NULL;
		s_ft = NULL;
		s_or = NULL;
		main_strnstr();
		return (0);
	}
	free (s1);
	free (s2);
	free (s_ft);
	free (s_or);
	s1 = NULL;
	s2 = NULL;
	s_ft = NULL;
	s_or = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_strtrim*///////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main_strtrim()
{
	char	*s1 = NULL;
	char	*s2 = NULL;
	char	press;

	char	*s_ft = (char *)calloc(100, sizeof(char));
	if (!s_ft) exit(1);

	//INSTRUCCIONES
	system("clear");
	printf("Elimina del String los caracteres que esten en SET por izda y derecha pero se detiene cuando no está en SET\n");
	printf("Para continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '1')
	{
		press = fill_null();
		switch (press)
		{
			case '1':
				s2 = (char *)calloc(100, sizeof(char));
				if (!s2) exit(1);
				s2 = fill_string(s2);
				break;
			case '2':
				s1 = (char *)calloc(100, sizeof(char));
				if (!s1) exit(1);
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
		printf("String a Trimar: ");
		s1 = (char *)calloc(100, sizeof(char));
		if (!s1) exit(1);
		s1 = fill_string(s1);
		printf("\nSet: ");
		s2 = (char *)calloc(100, sizeof(char));
		if (!s2) exit(1);
		s2 = fill_string(s2);
	}

	//SOLUCION
	system ("clear");
	printf("String1 = %s", s1);
	printf("\nSET = %s", s2);

	char *solucion = NULL;

	solucion = ft_strtrim(s1, s2);

	printf("\n\nTrimado: %s", solucion);
	fflush(stdout);
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s1);
		free (s2);
		free (s_ft);
		free (solucion);
		s1 = NULL;
		s2 = NULL;
		s_ft = NULL;
		solucion = NULL;
		main_strtrim();
		return (0);
	}
	free (s1);
	free (s2);
	free (s_ft);
	free (solucion);
	s1 = NULL;
	s2 = NULL;
	solucion = NULL;
	s_ft = NULL;
	return (0);
}


////////////////////////////////////////////////////////////
/*ft_substr*////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int	main_substr()
{
	//char	*ft_substr(char const *s, unsigned int start, size_t len)
	char			*s = NULL;
	char			*s_ft = (char *)calloc(100, sizeof(char));
	if (!s_ft) exit(1);
	unsigned int	num_start;
	size_t			num_len;
	char			press;

/*returns a substring from 's' starting from 'start' and max length of 'len'*/

	//INSTRUCCIONES
	system("clear");
	printf("Devuelve un sub-string de otro mas grande a partir del indice start hasta una longitud determinada\n");
	printf("Para continuar presione ENTER\n");
	getchar();

	//Sub menu principal
	press = options_null_valid();

	if (press == '2')
	{
		s = (char *)calloc(100, sizeof(char));
		if (!s) exit(1);
		s = fill_string(s);
	}

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

	char *solucion = NULL;

	solucion = ft_substr(s, num_start, num_len);
	printf("\n\nsub-String: %s", solucion);
	fflush(stdout); //para que write no este antes que el printf por el buffer
	press = repetimos_volvemos();
	if ((press == 'y') || (press == 'Y'))
	{
		free (s);
		free (s_ft);
		free (solucion);
		main_substr();
		return (0); //si no puede ir al otro free y liberar de nuevo. NO SE COMO. Supongo que por recursividad
	}
	free (s);
	free (s_ft);
	free (solucion);
	s = NULL;
	s_ft = NULL;
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


////////////////////////////////////////////////////////////
/*FUNCIONES PARA STRITERI y STRMAPI*////////////////////////
////////////////////////////////////////////////////////////


void ft_strupper(unsigned int index, char *c)
{
	(void)index; //para no usar index y eludir el -wall -wextra -werror
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

char ft2_strupper(unsigned int index, char c)
{
	(void)index; //para no usar index y eludir el -wall -wextra -werror
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

void ft_strlower(unsigned int index, char *c)
{
	(void)index;
	if (*c >= 'A' && *c <= 'Z')
		*c = *c + 32;
}

char ft2_strlower(unsigned int index, char c)
{
	(void)index;
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

void ft_struptolowtoup(unsigned int index, char *c)
{
	(void)index;
	if (*c >= 'A' && *c <= 'Z')
		*c = *c + 32;
	else if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

char ft2_struptolowtoup(unsigned int index, char c)
{
	(void)index;
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	else if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

void ft_strnext(unsigned int index, char *c)
{
	(void)index;
	if (ft_isprint(*c))
		*c = *c + 1;
}

char ft2_strnext(unsigned int index, char c)
{
	(void)index;
	if (ft_isprint(c))
		c = c + 1;
	return (c);
}

void ft_strinsertspace(unsigned int index, char *c)
{
	if (index % 2 != 0)
		*c = '*';
}

char ft2_strinsertspace(unsigned int index, char c)
{
	if (index % 2 != 0)
		c = '*';
	return (c);
}

////////////////////////////////////////////////////////////
/*FUNCIONES PARA LISTAS*////////////////////////////////////
////////////////////////////////////////////////////////////

void print_list(t_list *list, char *final)
{
	t_list	*aux = NULL;
	if (!list)
		return;
	fflush(stdout);
	aux = ft_lstlast(list);
	if (!aux)
		return ;
	while ((list) && (list->next))
	{
		if (*(char *)(aux->content) == *final)
		{
			if ((*(char *)list->next->content != *final) && (*(char *)list->content != *final))
			{
				write(1, list->content, 1);
				write(1, "-", 1);
			}
			else
			{
				if (*(char *)list->content != *final)
					write(1, list->content, 1);
				write(1, "-", 1);
				write(1, list->next->content, 1);
				//write(1, "\n", 1);
			}
		}
		else
		{
			write(1, list->content, 1);
			write(1, "-", 1);
			//write(1, "x", 1);
		}
		list = list->next;
	}
	if (*(char *)list->content != *final)
		write(1, list->content,1);
}



t_list	*lstpenultimo(t_list *lst)
{
	t_list *aux = NULL;

	if ((!lst) || (!lst->next)) //debe haber dos nodos minimo
		return (NULL);
	char *str = lst->content;
	while ((*str != '?') && (lst->next))
	{
		aux = lst;
		lst = aux->next;
		str = lst->content;
	}
	return (aux);
}

void	ft_lstadd_before_zero(t_list **lst, t_list *new, char *final)
{
	t_list	*aux = NULL;
	t_list	*aux_last = NULL;

	if (!new)
		return ;
	if (!*lst)
	{
		(void)aux_last;
		*lst = new;
		aux = ft_lstnew(final); //creamos el nodo final con \0
		ft_lstadd_back(lst, aux); //añadimos el nodo final al final de la lista
		/* if (!*lst)
			*lst = new;
		else
		{
			aux2 = ft_lstlast(*lst);
			aux2->next = new;
		} */




	}
	else
	{
		aux = lstpenultimo(*lst);
		aux_last = aux->next;
		aux->next = new;
		new->next = aux_last;
	}
}

//void	ft_lstclear(t_list **lst, void (*del)(void*))/
void	delete_content(void *content)
{
	if (content)
		free(content);
}
void	list_upper_lower(void *content)
{
	if (*(char *)content >= 'A' && *(char *)content <= 'Z')
		*(char *)content = *(char *)content + 32;
	else if (*(char *)content >= 'a' && *(char *)content <= 'z')
		*(char *)content = *(char *)content - 32;
}

void	*list_upper_lower2(void *content)
{
	char *a = NULL;

	a = (char *)calloc(1,1);
	if (!a)
		return (NULL);
	a = (char *)content;

	if (*a >= 'A' && *a <= 'Z')
		*a = *a + 32;
	else if (*a >= 'a' && *a <= 'z')
		*a = *a - 32;
	return (a);
}
