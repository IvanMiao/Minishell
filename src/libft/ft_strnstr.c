/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:08:13 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/14 17:29:50 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*petit;
	char	*grand;
	size_t	i;
	size_t	j;

	petit = (char *)little;
	grand = (char *)big;
	i = 0;
	if (little[0] == '\0')
		return (grand);
	while (grand[i] && i < len)
	{
		j = 0;
		while (grand[i + j] == petit[j] && i + j < len && grand[i + j])
		{
			j++;
			if (petit[j] == '\0')
				return (grand + i);
		}
		i++;
	}
	return (NULL);
}
