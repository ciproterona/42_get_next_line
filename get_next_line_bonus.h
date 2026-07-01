/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eroque-d <eroque-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 15:21:30 by eroque-d          #+#    #+#             */
/*   Updated: 2026/07/01 15:04:48 by eroque-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_LIMIT 4096

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

char	*ft_strjoin_gnl(char *s1, size_t s1_len, char const *s2, size_t s2_len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif // GET_NEXT_LINE_BONUS_H
