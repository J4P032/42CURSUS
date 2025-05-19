/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:06:31 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/19 11:43:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

bool	ft_manage_shlvl(char *input, char **envp, int i, int len)
{
	int	j;

	j = len + 1;
	free (envp[i]);
	while (input[j])
	{
		if (ft_isdigit(input[j++]))
			continue ;
		envp[i] = ft_strdup("SHLVL=0");
		return (1);
	}
	envp[i] = ft_strdup(input);
	return (1);
}

/*Check if the variable already is in the **envp.*/
/*1. if the input dont have an '=' it will exit with error 1 so nothing to do*/
/*2. search if the name of the variable in input is in the envp if not will...*/
/*...return 0 so will continue with code. If find it:*/
/*A. if find SHLVL will process it in a different funcion.*/
/*B. other will free it first to replace it with the new value (input) of it*/
bool	ft_check_variables(char *input, char **envp)
{
	int		i;
	int		len;
	char	*equal;

	equal = ft_strchr(input, '=');
	if (!equal)
		return (1);
	len = equal - input;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], input, len) == 0 && envp[i][len] == '=')
		{
			if (ft_strncmp("SHLVL", input, len) == 0)
				return (ft_manage_shlvl(input, envp, i, len), 1);
			free (envp[i]);
			envp[i] = ft_strdup(input);
			if (!envp[i])
				return (0); //CUIDADO AQUI!!! YO SALDRIA Y LIBERARIA TODO por que si no el programa continua como si nada y devuelve esa posicion como NULL lo cual habria dos NULL en envp y claro BUG
			return (1);
		}
		i++;
	}
	return (0);
}

/*1. checks if the variable already exists in envp if so, exit*/
/*2. if not create a new **new_env VAR with space for the new VAR plus the...*/
/*...the final NULL*/
void	ft_export(char *input, char ***envp)
{
	int		i;
	int		env_position;
	char	**new_env;

	if (ft_check_variables(input, *envp) == 1)
		return ;
	i = 0;
	env_position = 0;
	while ((*envp)[env_position])
		env_position++;
	new_env = ft_calloc(env_position + 2, sizeof(char *));
	if (!new_env)
		return ; //LIBERARMOS TODO Y FUERA CLEAN_ALL
	while (i < env_position) //SI SALE DE CHECK_VARIABLE con 0 al fallar el strdup no llegara al final de todo envp ya que uno por medio sera NULL
	{
		new_env[i] = ft_strdup((*envp)[i]);
		if (!new_env[i++])
			return (ft_matrix_free(new_env));
	}
	new_env[i++] = ft_strdup(input);
	if (new_env[i])//NO LO ENTIENDO (JAVI). si fuera if (envp[i]) si por que podriamos detectar el no NULL del fallo de envp pero si por si falla este strdup aqui, si se hacho sobre una i = 2, aqui estas compararon i = 3, ya que se incrementó en el strdup
		return (ft_matrix_free(new_env));
	ft_matrix_free(*envp);
	*envp = new_env;
}
