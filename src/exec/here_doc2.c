/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:45:30 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/23 14:57:26 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

//SIG_IGN pour ignorer. SIG_DFL pour reactive
//un fork car le parent peut continuer de tourner et ignorer
//le ctrl c temporairement. Dans l'enfant, on le reactive et si
//on tape ctrl c, seul l'enfant est tue.
//signal(SIGINT, sig_in_parent) pour gerer a nouveau normalement
//les signaux apres l'enfant.
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
		errors(3);
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		handle_child_process(cmd, env);
		free_all(env, token, cmd);
		exit(0);
	}
	waitpid(child, &status, 0);
	signal(SIGINT, sig_in_parent);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		return (unlink("./.heredoc.tmp"), 130);
	}
	return (0);
}
