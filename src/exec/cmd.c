/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:21:14 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/30 21:33:34 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static char	*get_name(t_token *token)
{
	bool	flag;

	while (token && token->type != PIPE)
	{
		flag = (token->type == WORD || token->type == DOLLAR);
		if (flag)
			break ;
		token = token->next;
	}
	if (!token)
		return (NULL);
	else
		return (token->str);
}

char	**get_env(t_env *env)
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
	res = (char **)mem_manager(MALLOC, sizeof(char *) * (i + 1), NULL);
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

void	free_cmd(t_cmd *cmd)
{
	char	**tmp;

	tmp = cmd->argv;
	while (*tmp)
		mem_manager(FREE, 0, *tmp++);
	mem_manager(FREE, 0, cmd->argv);
	tmp = cmd->envp;
	while (*tmp)
		mem_manager(FREE, 0, *tmp++);
	mem_manager(FREE, 0, cmd->envp);
	tmp = cmd->delimiter;
	while (*tmp)
		mem_manager(FREE, 0, *tmp++);
	mem_manager(FREE, 0, cmd->delimiter);
	mem_manager(FREE, 0, cmd);
}

t_cmd	*set_cmd(t_token *token, t_env *env, int *prev_pipe)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)mem_manager(MALLOC, sizeof(t_cmd), NULL);
	if (!cmd)
		return (NULL);
	cmd->name = get_name(token);
	cmd->argv = get_real_cmd(token, env);
	cmd->envp = get_env(env);
	cmd->pathname = cmd->argv[0];
	cmd->open_error = check_direction_file(token);
	cmd->infile = get_infile(token);
	cmd->outfile = get_outfile(token);
	cmd->delimiter = get_delimiter(token);
	cmd->append = check_append(token);
	cmd->fd = -1;
	cmd->prev_pipe = prev_pipe;
	return (cmd);
}
