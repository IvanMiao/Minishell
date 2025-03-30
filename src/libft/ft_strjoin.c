/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:22:00 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/26 15:26:06 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*p;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = -1;
	p = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
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

/*
int	main(void)
{
	char	*s1;
	char	*s2;
	char 	*p;

	s1 = "";
	s2 = "";
	p = ft_strjoin(s1, s2);
	printf("%s\n%s\n%s", s1, s2, p);
	return 0;
}
*/
