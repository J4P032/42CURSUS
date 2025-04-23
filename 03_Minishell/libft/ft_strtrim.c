/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:22:54 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:57:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*delete chars in 's1' that are in 'set' until it finds a char not in 'set'*/
/*the way to run over 's1' is from begining to end and then end to begin*/
/*example: s1=ababa set=a -> bab */ /*s1 = abcabcab set=ab -> cabc*/
/* ft_search_in_set is used to 'end' with each end-- index = 0 so will
return number of chars found in SET. if not found will return 0 */
/*end - start + (2 = 1 + 1). 1=\0, 1=because first element = 0*/
static	int	ft_search_in_set(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	while (s1[i])
	{
		j = 0;
		found = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (found)
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	start;
	size_t	end;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	start = ft_search_in_set(s1, set);
	if (start == s1_len)
		return (ft_calloc(1, sizeof(char)));
	end = s1_len - 1;
	while (end > start && ft_search_in_set(&s1[end], set))
		end --;
	dest = (char *)ft_calloc(end - start + 2, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[start], end - start + 2);
	return (dest);
}
