/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:01:13 by ymiao             #+#    #+#             */
/*   Updated: 2025/05/01 04:16:20 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/* the third argument of ft_strncmp is len(builtin) + 1,
	to be sure that exactly the builtin will be exectued
	otherwise, cd1, cdaaa, cdbonjour... will also be exectued*/

// for pipex, if there's a pipe, all builtin are executed in child
int	exec_builtin(t_cmd *cmd, t_env *env, t_token *token)
{
	int	flag;

	flag = -1;
	if (!cmd->pathname)
		return (flag);
	if (!ft_strncmp(cmd->pathname, "cd", 3))
		flag = ft_cd(env, cmd);
	if (!ft_strncmp(cmd->pathname, "pwd", 4))
		flag = ft_pwd(cmd->argv);
	if (!ft_strncmp(cmd->pathname, "env", 4))
		flag = ft_env(env);
	if (!ft_strncmp(cmd->pathname, "export", 7))
		flag = ft_export(env, cmd);
	if (!ft_strncmp(cmd->pathname, "unset", 6))
		flag = ft_unset(env, cmd);
	if (!ft_strncmp(cmd->pathname, "echo", 5))
		flag = ft_echo(cmd);
	if (!ft_strncmp(cmd->pathname, "exit", 5))
		flag = ft_exit(token, env, cmd, NULL);
	return (flag);
}

// for single cmd
int	exec_builtin_child(t_cmd *cmd, t_env *env, t_token *token)
{
	int	flag;

	(void)token;
	flag = -1;
	if (!ft_strncmp(cmd->pathname, "pwd", 4))
		flag = ft_pwd(cmd->argv);
	if (!ft_strncmp(cmd->pathname, "env", 4))
		flag = ft_env(env);
	if (!ft_strncmp(cmd->pathname, "echo", 5))
		flag = ft_echo(cmd);
	return (flag);
}

// for single cmd
int	exec_builtin_parent(t_cmd *cmd, t_env *env, t_token *token, t_shell *shell)
{
	int	flag;

	flag = -1;
	if (!cmd->pathname)
		return (flag);
	if (!ft_strncmp(cmd->pathname, "cd", 3))
		flag = ft_cd(env, cmd);
	if (!ft_strncmp(cmd->pathname, "export", 7))
		flag = ft_export(env, cmd);
	if (!ft_strncmp(cmd->pathname, "unset", 6))
		flag = ft_unset(env, cmd);
	if (!ft_strncmp(cmd->pathname, "exit", 5))
		flag = ft_exit(token, env, cmd, shell);
	return (flag);
}
