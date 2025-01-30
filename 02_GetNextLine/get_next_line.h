/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:27 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/30 20:41:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	int				*num_nodes;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
t_list	*ft_listnew(t_list **lst, char *content);
char	*ft_strchr(const char *s, int c);
void	ft_malloc_free(t_list **list, char **content, int option);
char	*compose_string(t_list *list);
int		ft_find_n(char *rest, const char *s, size_t n);
void	process_rest(t_list **list, char **rest);

#endif
