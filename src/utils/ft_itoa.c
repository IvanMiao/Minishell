/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:49:15 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/29 04:20:57 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr(char *tab, int i, int nb)
{
	tab[i] = '\0';
	i--;
	if (nb == 0)
		tab[0] = '0' + nb;
	if (nb < 0)
	{
		tab[0] = '-';
		nb = nb *(-1);
	}
	while (nb > 0)
	{
		tab[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		i;

	i = count(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tab = (char *)mem_manager(MALLOC ,sizeof(char) * (i + 1), NULL);
	if (tab == 0)
		return (0);
	ft_putnbr(tab, i, n);
	return (tab);
}
