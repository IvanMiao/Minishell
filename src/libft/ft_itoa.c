/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:46:39 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/15 15:57:43 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int		count;
	int		copy;

	count = 0;
	copy = n;
	if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		copy = -n;
		count += 1;
	}
	while (copy)
	{
		copy = copy / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ans;
	int		count;
	int		copy;

	count = count_len(n);
	copy = n;
	ans = (char *)malloc(sizeof(char) * (count + 1));
	if (!ans)
		return (NULL);
	if (n == 0)
		ans[0] = '0';
	else if (n < 0)
		ans[0] = '-';
	ans[count] = '\0';
	while (copy)
	{
		if (copy < 0)
			ans[count - 1] = -(copy % 10) + 48;
		else
			ans[count - 1] = (copy % 10) + 48;
		copy = copy / 10;
		count--;
	}
	return (ans);
}

/*
int	main(void)
{
	int	n;
	char	*p;

	n = 0;
	p = ft_itoa(n);
	printf("%d\n%s", n, p);
	return 0;
}
*/