/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:12:32 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

int			get_next_line(int fd, char **line);
char		*ft_strchr_gnl(const char *s, char c);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
char		*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char		*ft_strdup_gnl(const char *str);

#endif
