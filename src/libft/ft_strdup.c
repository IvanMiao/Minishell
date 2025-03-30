/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:48:50 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/14 17:57:11 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	len_s;
	size_t	i;

	i = 0;
	len_s = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len_s + 1));
	if (!new)
		return (NULL);
	while (i <= len_s)
	{
		new[i] = s[i];
		i++;
	}
	return (new);
}
