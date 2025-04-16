/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:01:13 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/16 22:56:00 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/* the third argument of ft_strncmp is len(builtin) + 1,
	to be sure that exactly the builtin will be exectued
	otherwise, cd1, cdaaa, cdbonjour... will also be exectued*/
int	exec_builtin(t_cmd *cmd, t_env *env, t_token *token)
{
	int	flag;

	flag = -1;
	if (!cmd->pathname)
		return (flag);
	if (!ft_strncmp(cmd->pathname, "cd", 3))
		flag = ft_cd(token, env);
	if (!ft_strncmp(cmd->pathname, "pwd", 4))
		flag = ft_pwd(cmd->argv);
	if (!ft_strncmp(cmd->pathname, "env", 4))
		flag = ft_env(env);
	if (!ft_strncmp(cmd->pathname, "export", 7))
		flag = ft_export(env, token);
	if (!ft_strncmp(cmd->pathname, "unset", 6))
		flag = ft_unset(env, token);
	if (!ft_strncmp(cmd->pathname, "echo", 5))
		flag = ft_echo(token);
	if (!ft_strncmp(cmd->pathname, "exit", 5))
	{
		ft_exit(token);
		flag = 0;
	}
	return (flag);
}
