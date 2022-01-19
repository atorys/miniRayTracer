/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:12:46 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void		*ft_calloc(size_t count, size_t size);

size_t		ft_strlen(const char *s);
size_t		ft_sigmlen(const char *str1, const char *str2);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n, int flag_len);

int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memset(void *dest, int c, size_t len);

long long	ft_atoi(const char *str);
double		ft_atod(const char *str);

char		*ft_strdup(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);

char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putnbr_fd(int n, int fd);

int			ft_isempty(const char *str);
int			ft_isdigit(int c);

#endif