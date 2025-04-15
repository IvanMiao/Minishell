/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 00:48:48 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/14 15:01:59 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);

char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_char(char *s1, char c);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);

char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);

void	ft_putchar_fd(int c, int fd);
void	ft_putstr_fd(char *s, int fd);

int		ft_fprintf(int fd, const char *s, char *str);

#endif
