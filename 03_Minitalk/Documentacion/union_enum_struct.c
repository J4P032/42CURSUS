typedef enum	e_type
{
	TYPE_INT, //0
	TYPE_FLOAT, //1
	TYPE_CHAR //2
} 				t_type;

typedef union	u_value //sizeof del tipo mas grande y solo usa dicha memoria uno de los valores incluidos.
{
	int		i;
	float	f;
	char	c;
}				t_value;

typedef struct	s_token
{
	t_value	type;
	t_value	value;
}				t_token;

/*La diferencia entre union y struct es que en el caso de la estructura:

typedef struct	s_value 
{
	int		i;
	float	f;
	char	c;
}				t_Svalue;
t_Svalue estructura; 
el sizeof(estructura) = sizeof(int) + sizeof(float) + sizeof(char) + padding para alinearlos. Es decir 
sizeof(estructura) = 4 + 4 + (1 + 3) seguramente 12bytes. El padding de 3 extra alinea el char de 1 con el float y el int de 4.asm

si embargo en el union

t_value	U_nion;
el sizeof(U_nion) = el tamaño del sizeof más grande, es decir solo 4 bytes. por lo que si hacemos un 

U_nion.i = 32;
printf("%d", U_nion.i) -> 32

U_nion.f = 0.5;
printf("%f", U_nion.f) -> 0.5
printf("%d", U_nion.i) -> corrupto YA QUE f pisa a i en ese momemnto.

*/
