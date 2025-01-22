
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	size_t i;

	i = 0;
	char **palabras = ft_split(argv[1], '-');
	while (palabras[i])
		printf("\n%s", palabras[i++]);
	i = 0;
	while (palabras[i])
	{
		free(palabras[i]);
		i++;
	}
	free(palabras);
	return 0;
}

