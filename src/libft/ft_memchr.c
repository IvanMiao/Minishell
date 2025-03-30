/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:19 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/14 16:31:40 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*p;
	size_t	i;

	p = (void *)s;
	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)p == (unsigned char)c)
			return (p);
		p++;
		i++;
	}
	return (NULL);
}
