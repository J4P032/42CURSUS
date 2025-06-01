/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:36:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/29 14:09:16 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../inc/minishell_j.h"

typedef struct s_lists
{
	void			*content;
	struct s_lists	*next;
}					t_lists;

typedef struct s_split
{
	char	*split_aux;
	char	*s;
	char	c;
	int		error;
	size_t	words;
	size_t	start;
	int		quotes;
}			t_split;	

int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_findstr(const char *s1, const char *s2, size_t l);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_lists **lst, t_lists *new);
void		ft_lstadd_front(t_lists **lst, t_lists *new);
void		ft_lstdelone(t_lists *lst, void (*del)(void *));
void		ft_lstclear(t_lists **lst, void (*del)(void*));
void		ft_lstiter(t_lists *lst, void (*f)(void *));
t_lists		*ft_lstlast(t_lists *lst);
t_lists		*ft_lstmap(t_lists *lst, void *(*f)(void *), void (*del)(void *));
t_lists		*ft_lstnew(void *content);
int			ft_lstsize(t_lists *lst);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_size(const char *str);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_utoa(unsigned int n);
void		ft_putnbr_base32(unsigned int *nbr, char *base, int *num_chars);
void		ft_putnbr_base(unsigned long *nbr, char *base, int *num_chars);

//MINISHELL - Mario
int			ft_strcmp(const char *s1, const char *s2);
void		ft_matrix_free(char ***matrix);
char		**ft_matrix_dup(char **matrix);
char		*ft_strchr_quotes(const char *s, int c);
char		*ft_strcat(char *dest, const char *src);
size_t		ft_strcspn(const char *str1, const char *str2);
int			ft_matrix_len(char **matrix);
char		**ft_matrix_dup_plus(char **env, int extra);
char		*ft_strjoin_r(char *s1, char const *s2);

//MINISHELL - Javi
char		**ft_split_quotes(char const *s, char c, t_input *input);
void		ft_input_free(t_input *input);
int			ft_count_quotes_words(t_split *squotes, t_input *input);
void		assign_token_status(t_input *input, t_split *sq, char letter);
char		*sub_split_quotes(t_split *squotes, t_input *input);
int			is_escaped(t_split *squotes, size_t i);
int			is_spaced(t_split *sq, size_t i);
int			is_quoted(t_input *input, int word);
long long	ft_atol(char *nptr, int *error);
char		*ft_first_word(char *str, char c);
char		*ft_last_str(char **str);
#endif
