/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:42:14 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/14 17:57:28 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	if (n != 0 && size != 0)
		if (size > 2147483647 || n > 2147483647 || size > 2147483647 / n)
			return (NULL);
	p = malloc(size * n);
	if (!p)
		return (NULL);
	if (size * n == 0)
		return (p);
	ft_bzero(p, size * n);
	return (p);
}
