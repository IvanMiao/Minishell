/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:29:25 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/07 11:46:18 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

//true if the strings are equal
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "echo", 4)
		|| !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 4)
		|| !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "unset", 5));
}

int	exec_builins(char **argv, t_env *env)
{
	if (!ft_strncmp(argv[0], "cd", 2))
		return (ft_cd());
	else if (!ft_strncmp(argv[0], "echo", 4))
		return (ft_echo());
	else if (!ft_strncmp(argv[0], "env", 3))
		return (ft_env(env));
	else if (!ft_strncmp(argv[0], "exit", 4))
		return (ft_exit());
	else if (!ft_strncmp(argv[0], "export", 6))
		return (ft_export());
	else if (!ft_strncmp(argv[0], "pwd", 3))
		return (ft_pwd());
	else if (!ft_strncmp(argv[0], "unset", 5))
		return (ft_unset(env,));
	return (1);
}
