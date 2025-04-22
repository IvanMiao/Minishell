/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/21 22:17:46 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/* expansion of all the dollar vars in char *str! */
static char	*heredoc_expand(char *str, t_env *env)
{
	char	*tmp;
	char	*env_word;
	char	*result;
	char	*result_expand;
	char	*char_str;
	int		i;
	int		j;

	i = 0;
	result_expand = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			j = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			tmp = ft_substr(str, j, i - j);
			if (ft_get_env(env, tmp))
				env_word = ft_strdup(ft_get_env(env, tmp));
			else
				env_word = ft_strdup("");
			free(tmp);
			result = ft_strjoin(result_expand, env_word);
			free(result_expand);
			result_expand = result;
			free(env_word);
			continue ;
		}
		else
		{
			char_str = ft_substr(str, i, 1);
			result = ft_strjoin(result_expand, char_str);
			free(result_expand);
			free(char_str);
			result_expand = result;
			i++;
		}
	}
	return (result_expand);
}

void	read_here_doc(char *delimiter, bool flag_expand, t_env *env)
{
	char	*str;
	char	*result_expand;
	int		fd;

	fd = open("./.heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open:");
		return ;
	}
	while (1)
	{
		str = readline("> ");
		if (ft_strlen(str) == ft_strlen(delimiter)
			&& ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0)
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
	return ;
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
