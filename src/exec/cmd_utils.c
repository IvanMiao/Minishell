/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:32:50 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/28 20:47:43 by ymiao            ###   ########.fr       */
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

static char	*get_builtin(char *first_cmd)
{
	char	*tmp;

	tmp = first_cmd;
	if (!ft_strncmp(first_cmd, "cd", 2) && ft_strlen(tmp) == 2)
		return ("cd");
	if (!ft_strncmp(first_cmd, "pwd", 3) && ft_strlen(tmp) == 3)
		return ("pwd");
	if (!ft_strncmp(first_cmd, "env", 3) && ft_strlen(tmp) == 3)
		return ("env");
	if (!ft_strncmp(first_cmd, "export", 6) && ft_strlen(tmp) == 6)
		return ("export");
	if (!ft_strncmp(first_cmd, "unset", 5) && ft_strlen(tmp) == 5)
		return ("unset");
	if (!ft_strncmp(first_cmd, "echo", 4) && ft_strlen(tmp) == 4)
		return ("echo");
	if (!ft_strncmp(first_cmd, "exit", 4) && ft_strlen(tmp) == 4)
		return ("exit");
	return (NULL);
}

char	*get_pathname(t_env *env, char *first_cmd)
{
	char	**all_path;
	char	*ans;
	char	*tmp;
	int		i;

	if (get_builtin(first_cmd) != NULL)
		return (ft_strdup(get_builtin(first_cmd)));
	if (ft_strlen(first_cmd) == 0 || access(first_cmd, F_OK | X_OK) == 0
		|| !ft_get_env(env, "PATH"))
		return (ft_strdup(first_cmd));
	i = 0;
	all_path = ft_split((const char *)ft_get_env(env, "PATH"), ':');
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		ans = ft_strjoin(tmp, first_cmd);
		free(tmp);
		if (access(ans, F_OK | X_OK) == 0)
			return (free_split(all_path), ans);
		free(ans);
		i++;
	}
	free_split(all_path);
	return (ft_strdup(first_cmd));
}

static int	count_cmd_arg(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD || tmp->type == DOLLAR)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_real_cmd(t_token *token, t_env *env)
{
	char	**cmd;
	int		i;

	i = count_cmd_arg(token);
	cmd = (char **)safe_malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOLLAR)
		{
			if (i == 0)
				cmd[i] = get_pathname(env, token->str);
			else
				cmd[i] = ft_strdup(token->str);
			i++;
		}
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
