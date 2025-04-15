/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:44:00 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/15 15:41:28 by cgerner          ###   ########.fr       */
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
	return ((resultat * sign) % 256);
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

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	token = token->next;
	while (token && token->type != PIPE)
	{
		count++;
		token = token->next;
	}
	return (count);
}

int	ft_exit(t_token *token)
{
	long long			nb;
	int					error;
	int					argc;
	t_token				*arg;

	printf("exit\n");
	argc = count_args(token);
	arg = token->next;
	if (arg)
	{
		if (!is_numeric(arg->str))
		{
			ft_fprintf(2,
					"minishell: exit: %s: numeric argument required\n", arg->str);
			exit(255);
		}
		nb = ft_atoi(arg->str, &error);
		if (error)
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", arg->str);
			exit(255);
		}
	}
	if (argc > 1)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n", NULL);
		return (-1);
	}
	exit(nb);
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
