/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:21:14 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/15 15:33:31 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

void	free_cmd(t_cmd *cmd)
{
	char	**tmp;

	tmp = cmd->argv;
	while (*tmp)
		free(*tmp++);
	free(cmd->argv);
	tmp = cmd->envp;
	while (*tmp)
		free(*tmp++);
	free(cmd->envp);
	free(cmd);
}

t_cmd	*set_cmd(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = get_real_cmd(token, env);
	cmd->envp = get_env(env);
	cmd->pathname = cmd->argv[0];
	cmd->infile = get_infile(token);
	cmd->outfile = get_outfile(token);
	cmd->delimiter = get_delimiter(token);
	cmd->append = check_append(token);
	return (cmd);
}

static void	all_dups(t_cmd *cmd, int *prev_pipe)
{
	int	fd_in;
	int	fd_out;

	if (prev_pipe == NULL)
		fd_in = -1;
	else
		fd_in = *prev_pipe;
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->delimiter)
	{
		fd_in = open("./.heredoc.tmp", O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->infile)
	{
		fd_in = open_file(cmd->infile, 0);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->outfile && cmd->append == false)
	{
		fd_out = open_file(cmd->outfile, 1);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (cmd->outfile && cmd->append == true)
	{
		fd_out = open_file(cmd->outfile, 2);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

int	exec_simple_cmd(t_token *token, t_env *env, int *prev_pipe)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		status;

	cmd = set_cmd(token, env);
	// printf("------------------------------\n");
	// printf(GREEN"cmd path is: %s\n"ENDCOLOR, cmd->pathname);
	// printf("infile is: %s\n", cmd->infile);
	// printf("outfile is: %s\n", cmd->outfile);
	// printf("delimiter is: %s\n", cmd->delimiter);
	// printf("append?: %s\n", cmd->append? "true" : "false");
	// printf("------------------------------\n");
	if (cmd->pathname && !ft_strlen(cmd->pathname))
		return (free_cmd(cmd), 0);
	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(token, env, cmd);
		all_dups(cmd, prev_pipe);
		if (exec_builtin(cmd, env, token) != -1 || !cmd->pathname)
		{
			free_all(env, token, cmd);
			exit(0);
		}
		execve(cmd->pathname, cmd->argv, cmd->envp);
		ft_fprintf(2, "minishell: %s: command not found\n", cmd->pathname);
		free_all(env, token, cmd);
		exit (127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd->delimiter)
			unlink("./.heredoc.tmp");
		if (*prev_pipe != -1)
			close(*prev_pipe);
		free_cmd(cmd);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

int	ft_exec(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	cmd = set_cmd(token, env);
	if (ft_strlen(cmd->pathname) == 0)
		return (free_cmd(cmd), 0);
	handle_here_doc(token, env, cmd);
	all_dups(cmd, NULL);
	if (exec_builtin(cmd, env, token) != -1)
	{
		free_all(env, token, cmd);
		exit (0);
	}
	if (execve(cmd->pathname, cmd->argv, cmd->envp) < 0)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd->pathname);
		free_all(env, token, cmd);
	}
	return (1);
}

/*printf(GREEN"cmd path is: %s\n"ENDCOLOR, cmd->pathname);
printf("infile is: %s\n", cmd->infile);
printf("outfile is: %s\n", cmd->outfile);
printf("delimiter is: %s\n", cmd->delimiter);
char	*ans = cmd->append? "true" : "false";
printf("append?: %s\n", ans);
printf("------------------------------\n");
*/