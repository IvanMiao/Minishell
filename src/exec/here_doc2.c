/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:45:30 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/29 04:46:34 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

void	handle_child_process(t_cmd *cmd, t_env *env)
{
	int		i;
	bool	flag_expand;
	char	*delimiter;

	i = 0;
	while (cmd->delimiter[i])
	{
		flag_expand = true;
		delimiter = remove_quotes(cmd->delimiter[i]);
		if (ft_strncmp(delimiter, cmd->delimiter[i]
				, ft_strlen(cmd->delimiter[i]) + 1) != 0)
			flag_expand = false;
		read_here_doc(delimiter, flag_expand, env, cmd);
		mem_manager(FREE, 0, delimiter);
		i++;
	}
}

int	handle_here_doc(t_token *token, t_env *env, t_cmd *cmd)
{
	pid_t	child;
	int		status;

	(void)token;
	if (!cmd->delimiter)
		return (0);
	signal(SIGINT, SIG_IGN);
	child = fork();
	if (child == -1)
		errors(3, token, env, cmd);
	if (child == 0)
	{
		handle_child_process(cmd, env);
		free_all(env, token, cmd);
		exit(0);
	}
	waitpid(child, &status, 0);
	signal(SIGINT, ctrl_c);
	if (cmd->fd >= 0)
		close(cmd->fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
