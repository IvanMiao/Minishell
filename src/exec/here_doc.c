/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/22 02:48:46 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

// static char	*heredoc_expand(char *str, t_env *env)
// {
// 	char	*tmp;
// 	char	*env_word;
// 	char	*result;
// 	char	*result_expand;
// 	char	*char_str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	result_expand = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1]
// 			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
// 		{
// 			i++;
// 			j = i;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			tmp = ft_substr(str, j, i - j);
// 			if (ft_get_env(env, tmp))
// 				env_word = ft_strdup(ft_get_env(env, tmp));
// 			else
// 				env_word = ft_strdup("");
// 			free(tmp);
// 			result = ft_strjoin(result_expand, env_word);
// 			free(result_expand);
// 			result_expand = result;
// 			free(env_word);
// 			continue ;
// 		}
// 		else
// 		{
// 			char_str = ft_substr(str, i, 1);
// 			result = ft_strjoin(result_expand, char_str);
// 			free(result_expand);
// 			free(char_str);
// 			result_expand = result;
// 			i++;
// 		}
// 	}
// 	return (result_expand);
// }

/* expansion of all the dollar vars in char *str! */
static char	*get_env_value(const char *str, int *pos, t_env *env)
{
	int		start;
	char	*var_name;
	char	*value;

	start = ++(*pos);
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
		(*pos)++;
	var_name = ft_substr(str, start, *pos - start);
	if (ft_get_env(env, var_name))
		value = ft_strdup(ft_get_env(env, var_name));
	else
		value = ft_strdup("");
	free(var_name);
	return (value);
}

static char	*heredoc_expand(char *str, t_env *env)
{
	char	*result;
	char	*tmp;
	int		i;
	char	c[2];
	char	*old;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			tmp = get_env_value(str, &i, env);
		else
		{
			c[0] = str[i++];
			c[1] = '\0';
			tmp = ft_strdup(c);
		}
		old = result;
		result = ft_strjoin(result, tmp);
		free(old);
		free(tmp);
	}
	return (result);
}

void	read_here_doc(char *delimiter, bool flag_expand, t_env *env)
{
	char	*str;
	char	*result_expand;
	int		fd;

	fd = open("./.heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		str = readline("> ");
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter) + 1))
		{
			free(str);
			break ;
		}
		if (flag_expand)
		{
			result_expand = heredoc_expand(str, env);
			ft_fprintf(fd, "%s\n", result_expand);
			free(result_expand);
		}
		else
			ft_fprintf(fd, "%s\n", str);
		free(str);
	}
	close(fd);
}

void	handle_here_doc(t_token *token, t_env *env, t_cmd *cmd)
{
	bool	flag_expand;
	char	*delimiter;

	(void)token; //tmp
	flag_expand = true;
	if (cmd->delimiter)
	{
		delimiter = remove_quotes(cmd->delimiter);
		if (ft_strncmp(delimiter, cmd->delimiter, ft_strlen(cmd->delimiter) + 1) != 0)
			flag_expand = false;
		read_here_doc(delimiter, flag_expand, env);
		free(delimiter);
	}
}
