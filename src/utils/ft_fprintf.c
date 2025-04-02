/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:54:16 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/02 16:19:41 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	conversions_csdi(char c, char *str, int count, int fd)
{
	if (c == 's')
	{
		ft_putstr_fd(str, fd);
		if (str == NULL)
			str = "(null)";
		count += (int)ft_strlen(str);
	}
	return (count);
}

static int	analyse_format(const char *s, char *str, int fd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != '%')
		{
			ft_putchar_fd(s[i], fd);
			count++;
		}
		else if (s[i] == '%' && s[i + 1])
		{
			count = conversions_csdi(s[i + 1], str, count, fd);
			i++;
		}
		i++;
	}
	return (count);
}

int	ft_fprintf(int fd, const char *s, char *str)
{
	int		count;

	if (ft_strlen((char *)s) == 0)
		return (0);
	else if (!s)
		return (-1);
	count = analyse_format(s, str, fd);
	return (count);
}
