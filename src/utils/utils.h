/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 00:48:48 by ymiao             #+#    #+#             */
/*   Updated: 2025/03/31 02:08:15 by ymiao            ###   ########.fr       */
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

void	*ft_calloc(size_t n, size_t size);
char	*ft_strdup(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
