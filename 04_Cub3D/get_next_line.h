/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:27 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 12:23:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_doc
{
	char			*content;
	ssize_t			r_bytes;
	ssize_t			*total_rbytes;
	struct s_doc	*next;
}					t_doc;

char	*get_next_line(int fd);
char	*process_rest(char **big, char **rest, ssize_t *rbytes, t_doc **lst);
char	*str_join(char *dest, char *src, char *rest, ssize_t length);
char	*ft_read_fd(int fd, ssize_t *bytes, t_doc **list);
ssize_t	findn( size_t n, const char *s, int option);
t_doc	*ft_listnew(t_doc **lst, char **content, ssize_t *rbytes);
char	*compose_string(t_doc **list);
char	*give_me_rest(t_doc **l, char **content, int option, ssize_t *b);
void	free_list(t_doc **list, int option);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
