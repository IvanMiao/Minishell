/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_part3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:56:14 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/22 16:28:57 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin_char(char *s1, char c)
{
	size_t	len_s1;
	size_t	i;
	char	*p;

	len_s1 = ft_strlen(s1);
	i = -1;
	p = malloc(sizeof(char) * (len_s1 + 2));
	if (!p)
		return (NULL);
	while (++i < len_s1)
		p[i] = s1[i];
	p[i++] = c;
	p[i] = '\0';
	return (p);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	a;
	size_t	b;
	char	*buf1;
	char	*buf2;

	a = 0;
	b = 0;
	buf1 = (char *) s1;
	buf2 = (char *) s2;
	if (buf2[0] == '\0')
		return (buf1);
	while (a < len && buf1[a] != '\0')
	{
		b = 0;
		while (buf1[a + b] == buf2[b] && a + b < len)
		{
			if (buf2[b + 1] == '\0')
				return (buf1 + a);
			b++;
		}
		a++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
