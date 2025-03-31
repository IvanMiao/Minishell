/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:44:00 by cgerner           #+#    #+#             */
/*   Updated: 2025/03/31 02:08:50 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

long long	ft_atoi_2(char *str, int *error, int *i)
{
	long long	resultat;
	int			sign;

	resultat = 0;
	sign = 1;
	*error = 0;
	if (str[*i] == '-')
		sign *= -1;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	while (ft_isdigit(str[*i]))
	{
		if (resultat > (LLONG_MAX - (str[*i] - '0')) / 10)
		{
			*error = 1;
			if (sign == 1)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		resultat = resultat * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (resultat * sign);
}

long long	ft_atoi(char *str, int *error)
{
	int	i;

	i = 0;
	*error = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (ft_atoi_2(str, error, &i));
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(int argc, char **argv)
{
	long long			nb;
	int					error;

	printf("exit\n");
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
			return (printf("bash: exit: %s: numeric argument required\n",
					argv[1]), 255);
		nb = ft_atoi(argv[1], &error);
		if (error)
			return (printf("bash: exit: %s: numeric argument required\n",
					argv[1]), 255);
	}
	if (argc > 2)
	{
		printf("bash: exit: too many arguments\n");
		return (-1);
	}
	return ((int)nb);
}

/*
int	main(int argc, char **argv)
{
	int	exit_code;

	exit_code = ft_exit(argc, argv);
	if (exit_code == -1)
		return (1);
	// printf("%lld\n", LLONG_MIN);
	return (exit_code);
}
*/