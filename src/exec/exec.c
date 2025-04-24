/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:05:52 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/24 12:46:52 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static t_cmd	*prepare_cmd(t_token *token, t_env *env, int *exit_code)
{
	t_cmd	*cmd;

	cmd = set_cmd(token, env);
	*exit_code = check_cmd(cmd, token, env);
	if (*exit_code != -1)
		return (free_cmd(cmd), NULL);
	*exit_code = exec_builtin_parent(cmd, env, token);
	if (*exit_code != -1)
		return (free_cmd(cmd), NULL);
	*exit_code = handle_here_doc(token, env, cmd);
	if (*exit_code != 0)
		return (free_cmd(cmd), NULL);
	return (cmd);
}

static void	exec_simpcmd_child(t_cmd *cmd, t_env *env, t_token *token)
{
	sig_in_child();
	all_dups(cmd, NULL);
	if (exec_builtin_child(cmd, env, token) != -1)
	{
		free_all(env, token, cmd);
		exit(0);
	}
	execve(cmd->pathname, cmd->argv, cmd->envp);
	error_execve(cmd, env, token);
}

int	exec_simple_cmd(t_token *token, t_env *env)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		status;
	int		exit_code;

	exit_code = -1;
	cmd = prepare_cmd(token, env, &exit_code);
	if (!cmd)
		return (exit_code);
	pid = fork();
	if (pid == -1)
		errors(3);
	if (pid == 0)
		exec_simpcmd_child(cmd, env, token);
	sig_in_parent(1);
	waitpid(pid, &status, 0);
	sig_in_parent(2);
	if (cmd->delimiter)
		unlink("./.heredoc.tmp");
	free_cmd(cmd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	exec_child(t_token *token, t_env *env, t_cmd *cmd, int *prev_pipe)
{
	int	exit_builtin;

	all_dups(cmd, prev_pipe);
	exit_builtin = exec_builtin(cmd, env, token);
	if (exit_builtin != -1)
	{
		free_all(env, token, cmd);
		exit (exit_builtin);
	}
	if (execve(cmd->pathname, cmd->argv, cmd->envp) < 0)
		error_execve(cmd, env, token);
	return (1);
}

pid_t	last_cmd(t_token *token, t_env *env, int *prev_pipe)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		exit_code;

	cmd = set_cmd(token, env);
	exit_code = check_cmd(cmd, token, env);
	if (exit_code != -1)
		return (free_cmd(cmd), exit_code);
	if (cmd->delimiter[0])
		handle_here_doc(token, env, cmd);
	pid = fork();
	if (pid == -1)
		errors(3);
	if (pid == 0)
	{
		sig_in_child();
		all_dups(cmd, prev_pipe);
		exec_child(token, env, cmd, prev_pipe);
	}
	sig_in_parent(1);
	free_cmd(cmd);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	return (pid);
}
