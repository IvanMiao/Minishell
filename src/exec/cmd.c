/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:21:14 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/07 15:50:20 by ymiao            ###   ########.fr       */
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
	// for test
	printf("infile is :%s\n", cmd->infile);
	printf("outfile is :%s\n", cmd->outfile);
	printf("delimiter is :%s\n", cmd->delimiter);
	printf("append? :%d\n", cmd->append);
	// test done
	return (cmd);
}

int	exec_simple_cmd(t_token *token, t_env *env)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		status;
	//int		fd;

	pid = fork();
	if (pid == 0)
	{
		cmd = set_cmd(token, env);

		// if (cmd->infile)
		// 	fd = open(cmd->infile, O_RDONLY);
		// if (fd == -1)
		// {
		// 	perror("open");
		// 	free_cmd(cmd);
		// 	exit(1);
		// }
		
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
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
