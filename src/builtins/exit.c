/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:44:00 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/23 18:09:09 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

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

static long long	ft_atoi_exit_2(char *str, int *error, int *i)
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

static long long	ft_atoi_exit(char *str, int *error)
{
	int	i;

	i = 0;
	*error = 0;
	if (!str)
		return (0);
	if (!is_numeric(str))
	{
		*error = 2;
		return (-1);
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (ft_atoi_exit_2(str, error, &i));
}

int	ft_exit(t_token *token, t_env *env, t_cmd *cmd)
{
	long long	nb;
	int			error;
	int			argc;

	printf("exit\n");
	argc = 0;
	while (cmd->argv[argc])
		argc++;
	nb = ft_atoi_exit(cmd->argv[1], &error);
	if (error)
	{
		ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
			cmd->argv[1]);
		free_all(env, token, cmd);
		if (error == 2)
			exit(2);
		exit(255);
	}
	if (argc > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n", NULL);
		return (1);
	}
	free_all(env, token, cmd);
	exit(nb);
}
