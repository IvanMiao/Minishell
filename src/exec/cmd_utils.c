/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:32:50 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/07 16:34:50 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static void	free_split(char **all_path)
{
	int	i;

	i = 0;
	if (!all_path)
		return ;
	while (all_path[i])
	{
		free(all_path[i]);
		i++;
	}
	free(all_path);
}

char	*get_pathname(t_env *env, char *first_cmd)
{
	char	**all_path;
	char	*ans;
	char	*tmp;
	int		i;

	i = 0;
	if (access(first_cmd, F_OK | X_OK) == 0 || !ft_get_env(env, "PATH"))
		return (first_cmd);
	all_path = ft_split((const char *)ft_get_env(env, "PATH"), ':');
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		ans = ft_strjoin(tmp, first_cmd);
		free(tmp);
		if (access(ans, F_OK | X_OK) == 0)
		{
			free_split(all_path);
			return (ans);
		}
		free(ans);
		i++;
	}
	free_split(all_path);
	return (first_cmd);
}

char	**get_real_cmd(t_token *token, t_env *env)
{
	char	**cmd;
	bool	flag;
	int		i;
	t_token	*tmp;

	tmp = token;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == DOLLAR)
			i++;
		tmp = tmp->next;
	}

	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (token && token->type != PIPE)
	{
		flag = (token->type == WORD || token->type == DOLLAR);
		if (!flag)
		{
			token = token->next;
			continue ;
		}
		if (i == 0)
			cmd[i] = get_pathname(env, ft_strdup(token->str));
		else
			cmd[i] = ft_strdup(token->str);
		printf("check cmd[%d]: %s\n", i, cmd[i]);
		i++;
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
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
