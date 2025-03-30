/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:29:35 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/14 20:08:11 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_char(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_word(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	count;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (check_char(s1[start], set))
		start++;
	if (!check_char(s1[end], set))
		count = end - start + 1;
	while (check_char(s1[end], set))
	{
		if (end <= start)
		{
			count = 0;
			break ;
		}
		end--;
		count = end - start + 1;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	count;
	char	*copy;

	i = -1;
	count = count_word(s1, set);
	start = 0;
	while (check_char(s1[start], set))
		start++;
	copy = malloc(sizeof(char) * (count + 1));
	if (!copy)
		return (NULL);
	while (++i < count)
		copy[i] = s1[start + i];
	copy[i] = '\0';
	return (copy);
}

/*
int	main(void)
{
	char	*p;
	p = ft_strtrim("   xxx   xxx", " x");

	return 0;
}
*/