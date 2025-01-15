
/*ft_memcpy*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char **argv)
{
	if (argc != 4)
	{
		printf("parametros: (string) (num offset sobre origen) (num de chars)");
		return (0);
	}
	unsigned char *source1 = (unsigned char *)argv[1];
	unsigned char *source2 = (unsigned char *)argv[1];
	unsigned char *dest1;
	unsigned char *dest2;
	int offset = atoi(argv[2]);
	int	num = atoi(argv[3]);

	dest1 = source1 + offset;
	dest2 = source2 + offset;
	ft_memcpy(dest1, source1, num);
	memcpy(dest2, source2, num);
	printf("ft_: %s", dest1);
	printf("\nori: %s", dest2);
	printf("\nfinal de programa");
	return (0);
}

/*ft_memcpy2*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main ()
{

	unsigned char *source1 = NULL;
	unsigned char *source2 = NULL;
	unsigned char *dest1 = NULL;
	unsigned char *dest2 = NULL;
	int num = 0;

	ft_memcpy(dest1, source1, num);
	memcpy(dest2, source2, num);
	printf("ft_: %s", dest1);
	printf("\nori: %s", dest2);
	printf("\nfinal de programa");
	return (0);
}

/*ft_memmove*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char **argv)
{
	size_t i = 0;
	if (argc != 4)
	{
		printf("parametros: (string) (offset) (num de chars)");
		return (0);
	}
	unsigned char *source1 = (unsigned char *)malloc(strlen(argv[1]) + 3);
	unsigned char *source2 = (unsigned char *)malloc(strlen(argv[1]) + 3);
	while (argv[1][i])
	{
		source2[i+2] = argv[1][i];
		source1[i+2] = argv[1][i];
		i++;
	}
	source1[i] = '\0';
	source2[i] = '\0';

	int offset = atoi(argv[2]);
	int	num = atoi(argv[3]);

	unsigned char *dest1 = source1 + offset;
	unsigned char *dest2 = source2 + offset;

	ft_memmove(dest1, source1, num);
	memmove(dest2, source2, num);

	i = 0;
	write(1, "\nft_:", 5);
	while (i < strlen(argv[1]) + 3)
	{
		write(1, &dest1[i], 1);
		i++;
	}
	write(1, "\nori:", 5);
	i = 1;
	while (i < strlen(argv[1]) + 3)
	{
		write(1, &dest2[i], 1);
		i++;
	}

	write(1, "\nFIN", 4);

	free (source1);
	free (source2);
	return (0);
}


/*ft_memmove2*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char **argv)
{
	if (argc != 3)
	{
		printf("parametros: (offset) (num de chars)");
		return (0);
	}
	unsigned char source1[] = "con\0sec\0\0te\0tur";
	unsigned char source2[] = "con\0sec\0\0te\0tur";
	int offset = atoi(argv[1]);
	int	num = atoi(argv[2]);

	unsigned char *dest1 = source1 + offset;
	unsigned char *dest2 = source2 + offset;
	//dest1 = NULL;
	//dest2 = NULL;

	ft_memmove(dest1, source1, num);
	memmove(dest2, source2, num);

	printf("\nft_: %s", dest1);
	printf("\nori: %s", dest2);
	printf("\nfinal de programa");

	return (0);
}





/*ft_strnstr.c incluir cc -Wall -Wextra -Werror ft_strnstr.c -lbsd para compilar */
#include <stdlib.h>
#include <bsd/string.h>
int main(int argc, char **argv)
{
	if (argc != 4)
		return (0);
	const char *largo = argv[1];
	const char *busca = argv[2];
	size_t num = atoi(argv[3]);

	printf("%zu", num);
	char *solucion1 = ft_strnstr(largo, busca, num);
	char *solucion2 = strnstr(largo, busca, num);
	//char *solucion1 = ft_strnstr("aaabcabcd", "aabc", -1);
	//char *solucion2 = strnstr("aaabcabcd", "aabc", -1);
	//char *solucion1 = ft_strnstr("abcabcd", "abcd", 7);
	//char *solucion2 = strnstr("abcabcd", "abcd", 7);

	printf("\n%s", solucion1);
	printf("\n%s", solucion2);
	return (0);
}

