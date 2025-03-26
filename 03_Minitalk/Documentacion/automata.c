int	traductor_char_to_token(char c)
{
	if (c == '+')
		return (1);
	if (ft_isdigit(c) == 1)
		return (2);
	return (0);
}
//[automata.png]
//arg: 123+
int	get_state(int current_state, int token_char)
{
	const int matrix[][4] ={
		{1, 2, 3}, // 0 estado inicial
		{1, 1, 1}, // 1 estado de error
		{1, 1, 3}, // 2 estado + NO ACEPTACION
		{1, 1, 3}, // 3 ESTADO n OK
	};//err +  n
	//   0  1  2
	return (matrix[current_state][token_char]);
}


int	evaluate_string(char *str)
{
	int	token_char;
	int	state;
	int	i;

	state = 0;
	i = 0;
	while (str[i])
	{
		token_char = traductor_char_to_token(str[i]);
		state = get_state(state, token_char);
		i++;
	}
	if (state != 3)
		printf("Error, invalid input: %s\n", str);
	return (0);
}

/*Teniendo esto, si vamos pidiendo estados y el ultimo estado es diferente de 3,
entonces lanzamos un error. Por ejemplo. Tengamos como argumento +12
1. evaluate_string lanza el '+'
	token_char = 1 || state = get_state(0, 1) -> 2 que es estado de + NO ACEPTACION
2. evaluate_string lanza el '1'
	token_char = 2 || state = get_state(2, 2) -> 3. El estado era 2 lanzado por el anterior
3. evaluate_string lanza el '2'
	token_char = 2 || state = get_state(3, 2) -> 3.
como no lanza mas el ultimo estado es el 3, que si lo comparasemos despues es correcto
imaginemos que hubiera sido un +12e
4. evaluate_string lanza el 'e'
	token_char = 0 || state = get_state(3, 0) -> 1
que es un estado de error! es decir el automata te ayuda a establecer estados finales.
si hubiera sido un ++12
el primer estado hubiera sido un 2 como se vio, pero al lanzar el siguiente '+'
	token_char = 1 || state = get_state(2, 1) -> 1.
como ya es estado de error, no se continuaría
*/


