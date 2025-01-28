/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:27 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/28 14:26:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 42

typedef struct	s_list
{
	char 			*content;
	struct s_buffer	*next;
} 					t_list;

char	*get_next_line(int fd);
t_list	*ft_listnew(t_list **lst, void *content);
char	*ft_strchr(const char *s, int c);
void	ft_malloc_free(t_list **list, char **content, int option);

#endif
