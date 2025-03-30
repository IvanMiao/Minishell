/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:00:21 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/14 16:16:12 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	int		i;

	i = ft_strlen(s);
	p = (char *)s;
	p += i;
	if (*p == (char)c)
		return (p);
	p--;
	i--;
	while (i >= 0)
	{
		if (*p == (char)c)
			return (p);
		p--;
		i--;
	}
	return (NULL);
}
