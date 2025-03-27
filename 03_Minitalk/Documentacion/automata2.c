typedef enum	e_type
{
	INIT_STATE, //0 
	ERRO_STATE, //1 error
	PEND_STATE, //2 pending
	VALI_STATE //3 valid
} 				t_type;

int	traductor_char_to_token(char c)
{
	if (c == '+')
		return (PEND_STATE);
	if (ft_isdigit(c) == 1)
		return (VALI_STATE);
	return (ERRO_STATE);
}

int	get_state(int current_state, int token_char)
{
	const int matrix[][4] ={
		{ERRO_STATE, PEND_STATE, VALI_STATE}, // 0 estado inicial
		{ERRO_STATE, ERRO_STATE, ERRO_STATE}, // 1 estado de error
		{ERRO_STATE, ERRO_STATE, VALI_STATE}, // 2 estado + NO ACEPTACION
		{ERRO_STATE, ERRO_STATE, VALI_STATE}, // 3 ESTADO n OK
	};//err +  n
	//   0  1  2
	return (matrix[current_state][token_char]);
}


int	evaluate_string(char *str)
{
	int	token_char;
	int	state;
	int	i;

	state = INIT_STATE;
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

/*es lo mismo que el primer código pero más legible.
la forma de componer la matriz es como un sudocu
0 - la primera fila o estado inicial, solo puede ir a 3 estados, 
	el 1, 2 ó 3. Por lo que ponemos dichos estados.
1 - el estado de error, nunca se podrá salir de el, ya que 
	una vez alcanzado un error, siempre se ha de establecer en el
	así que todos serar errores.asm
2 - El estado de aceptacion de una sola '+' si es un digito sera un valido (indice 2)
	pero si vuelve a salir otro '+' (indice 1) debe comunicar con el estado de error
	aparte que si es otra cosa sería error, por lo que sería la fila (1, 1, 3)
3 - lo mismo que el dos. Una vez ha salido ya el primer numero, si es un digito (2) será valido
	por lo que el indice 2 (el tercero) será VALI_STATE
	PERO si vuelve a salir un token '+' (1 - segundo) u otra cosa (0 - primero)
	los dos seran errores.	
*/
