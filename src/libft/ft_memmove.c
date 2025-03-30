/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:51:47 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/15 23:44:45 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	if (src == NULL && dest == NULL)
		return (NULL);
	s = (const char *)src;
	d = (char *)dest;
	if (s > d)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

/*
int	main(void)
{
	char *src = "thanks to @apellicc for this test !\r\n";
 	char dst1[0xF0];
 	int size = strlen(src);
 	char *r1 = memmove(dst1, src, size);
 	char *r2 = ft_memmove(dst1, src, size);
 
	printf("%s\n%s", r1, r2);
 	r1 = memmove("", "" - 1, 0);
 	r2 = ft_memmove("", "" - 1, 0);
	printf("%s\n%s", r1, r2);

	int	n = 2;
	while (--n)
		printf("\nn:%d",n);
}
*/
