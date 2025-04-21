/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/21 16:38:59 by cgerner          ###   ########.fr       */
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
			env_word = ft_get_env(env, tmp);
			free(tmp);
			if (!env_word)
				env_word = ft_strdup("");
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
			result_expand = result;
			i++;
		}
	}
	return (result_expand);
}

void	read_here_doc(char *delimiter, bool flag_expand, t_env *env, int i)
{
	char	*str;
	char	*result_expand;
	int		fd;

	fd = open("./heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		str = readline("> ");
		if (!str || (ft_strlen(str) == ft_strlen(delimiter)
				&& ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0))
		{
			if (i == 1)
			{
				close(fd);
				unlink("./heredoc.tmp");
				fd = open("./heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
					return ;
				break ;
			}
			else if (i == 0)
			{
				close (fd);
				free(str);
				break ;
			}
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
	return ;
}

void	handle_here_doc(t_token *token, t_env *env, t_cmd *cmd)
{
	bool	flag_expand;
	char	*delimiter;
	int		i;
	int		i_max;

	(void)token;
	i = 0;
	i_max = 0;
	while (cmd->delimiter[i_max])
		i_max++;
	if (!cmd->delimiter)
		return ;
	while (cmd->delimiter[i])
	{
		flag_expand = true;
		delimiter = remove_quotes(cmd->delimiter[i]);
		if (ft_strncmp(delimiter, cmd->delimiter[i]
				, ft_strlen(cmd->delimiter[i]) + 1) != 0)
			flag_expand = false;
		if (i != i_max - 1)
			read_here_doc(delimiter, flag_expand, env, 1);
		else
			read_here_doc(delimiter, flag_expand, env, 0);
		free(delimiter);
		i++;
	}
}
