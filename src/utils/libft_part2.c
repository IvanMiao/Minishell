/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 00:50:22 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/29 04:22:16 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	len_s;

	i = 0;
	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if (len > len_s - start)
		len = len_s - start;
	dest = (char *)mem_manager(MALLOC, sizeof(char) * (len + 1), NULL);
	if (!dest)
		return (NULL);
	while (i < len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)mem_manager(MALLOC, sizeof(char) * ft_strlen(&s[i]) + 1, NULL);
	if (dest == NULL)
		return (0);
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*p;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = -1;
	p = (char *)mem_manager(MALLOC, sizeof(char) * (len_s1 + len_s2 + 1), NULL);
	if (!p)
		return (NULL);
	while (++i < len_s1)
		p[i] = s1[i];
	while (i < len_s1 + len_s2)
	{
		p[i] = s2[i - len_s1];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
