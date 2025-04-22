/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:21:14 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/22 16:19:38 by cgerner          ###   ########.fr       */
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
	tmp = cmd->delimiter;
	while(*tmp)
		free(*tmp++);
	free(cmd->delimiter);
	free(cmd);
}

t_cmd	*set_cmd(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
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
	return (cmd);
}
