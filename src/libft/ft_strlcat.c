/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:43:38 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/13 16:57:53 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
size_t strlcat (char * dst, const char * src, size_t siz)

Concatenate two strings. Appends src to string dst of size siz (unlike
strncat(), siz is the full size of dst, not space left). At most siz-1
characters will be copied. Always NULL terminates (unless siz <= strlen(dst)).

	Returns
The strlcat() function returns strlen(src) + MIN(siz,strlen(initial dst)).
If retval >= siz, truncation occurred.
*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (size <= len_dest)
		return (size + len_src);
	i = 0;
	while (len_dest + i < size - 1 && src[i])
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
