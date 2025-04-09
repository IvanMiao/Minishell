/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:21:14 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/08 04:36:45 by ymiao            ###   ########.fr       */
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

int	exec_simple_cmd(t_token *token, t_env *env)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		status;
	int		fd_in;
	int		fd_out;

	pid = fork();
	cmd = set_cmd(token, env);
	if (pid == 0)
	{
		// for test
		printf(GREEN"cmd path is: %s\n"ENDCOLOR, cmd->pathname);
		printf("infile is: %s\n", cmd->infile);
		printf("outfile is: %s\n", cmd->outfile);
		printf("delimiter is: %s\n", cmd->delimiter);
		printf("append?: %d\n", cmd->append);
		printf("------------------------------\n");
		// test done

		handle_here_doc(token, env, cmd);

		if (cmd->infile)
		{
			fd_in = open_file(cmd->infile, 0);
			dup2(fd_in, 0);
		}
		else if (cmd->outfile && cmd->append == false)
		{
			fd_out = open_file(cmd->outfile, 1);
			dup2(fd_out, 1);
		}
		else if (cmd->outfile && cmd->append == true)
		{
			fd_out = open_file(cmd->outfile, 2);
			dup2(fd_out, 1);
		}
		else if (cmd->delimiter)
		{
			fd_in = open("./.heredoc.tmp", O_RDONLY);
			dup2(fd_in, 0);
		}
		if (execve(cmd->pathname, cmd->argv, cmd->envp) < 0)
		{
			free_cmd(cmd);
			perror("execve");
			exit (1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (cmd->delimiter)
			unlink("./.heredoc.tmp");
		free_cmd(cmd);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
