/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:21:14 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/07 05:18:19 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static char	**get_cmd(t_token *token)
{
	char	**cmd;
	bool	flag;
	int		i;
	t_token	*tmp;

	tmp = token;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		flag = (token->type == R_IN || token->type == R_OUT
			|| token->type == R_DELIMITER || token->type == R_REDIRECTION
			|| token->type == INFILE || token->type == OUTFILE);
		if (!flag)
			i++;
		tmp = tmp->next;
	}

	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (token && token->type != PIPE)
	{
		flag = (token->type == R_IN || token->type == R_OUT
			|| token->type == R_DELIMITER || token->type == R_REDIRECTION
			|| token->type == INFILE || token->type == OUTFILE);
		if (flag)
		{
			token = token->next;
			continue ;
		}
		cmd[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	cmd[i] = NULL;
	// for test
	for (int j = 0; j<i; j++)
		printf("cmd[%d] : %s\n", j, cmd[j]);
	// end test
	return (cmd);
}

static char	**get_env(t_env *env)
{
	char	**res;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (env)
	{
		res[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}

int	exec_simple_cmd(t_token *token, t_env *env)
{
	pid_t	pid;
	char	**cmd;
	char	**envp;
	char	**tmp;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		cmd = get_cmd(token);
		envp = get_env(env);
		if (execve(cmd[0], cmd, envp) < 0)
		{
			tmp = cmd;
			while (*tmp)
				free(*tmp++);
			free(cmd);
			tmp = envp;
			while (*tmp)
				free(*tmp++);
			free(envp);
			perror("execve");
			exit (1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return(WEXITSTATUS(status));
	}
	return (0);
}