/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:01:13 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/11 12:55:20 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	exec_builtin(t_cmd *cmd, t_env *env, t_token *token)
{
	int	flag;

	flag = -1;
	if (!ft_strncmp(cmd->pathname, "cd", 2))
		flag = ft_cd(token->next->str);
	if (!ft_strncmp(cmd->pathname, "pwd", 3))
		flag = ft_pwd();
	if (!ft_strncmp(cmd->pathname, "env", 3))
		flag = ft_env(env);
	if (!ft_strncmp(cmd->pathname, "export", 6))
		flag = ft_export(env, token->next->str);
	if (!ft_strncmp(cmd->pathname, "unset", 5))
		flag = ft_unset(env, token->next->str);
	if (!ft_strncmp(cmd->pathname, "echo", 4))
		flag = ft_echo(token);
	if (!ft_strncmp(cmd->pathname, "exit", 4))
		flag = ft_exit(token);
	if (flag != -1)
		free(cmd);
	return (flag);
}
