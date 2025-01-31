/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:27 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/31 22:40:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	ssize_t			read_bytes;
	ssize_t			total_rbytes;
	struct s_list	*next;
}					t_list;

char	*ft_read_fd(int fd, ssize_t *bytes);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_find_n(const char *s, size_t n);
t_list	*ft_listnew(t_list **lst, char *content, ssize_t rbytes);
char	*get_next_line(int fd);
void	free_list(t_list **list, t_list **last);
char	*compose_string(t_list **list, t_list **last, char *aux_last);
char	*process_last(t_list **last);
void	copy_content(char *line, t_list *node, t_list *last, size_t node_i);

#endif
