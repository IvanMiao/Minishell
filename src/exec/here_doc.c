/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/16 18:47:28 by cgerner          ###   ########.fr       */
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
			j = i + 1;
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
		}
		else
		{
			char_str = ft_substr(str, i, 1);
			result = ft_strjoin(result_expand, char_str);
			free(result_expand);
			result_expand = result;
			i++;
		}
		i++;
	}
	return (result_expand);
}

void	read_here_doc(char *limiter, bool flag_expand, t_env *env)
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
		if (!str)
			break ;
		if (ft_strlen(str) == ft_strlen(limiter)
			&& ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			break ;
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

void	here_doc(t_token *token, t_env *env, t_cmd *cmd, bool flag_expand)
{
	(void) env;
	if (!token)
		return ;
	read_here_doc(cmd->delimiter, flag_expand, env);
}

void	handle_here_doc(t_token *token, t_env *env, t_cmd *cmd)
{
	bool	flag_expand;
	char	*delimiter;

	flag_expand = true;
	while (token)
	{
		if (token->type == R_DELIMITER && token->next)
		{
			delimiter = remove_quotes(token->next->str);
			if (ft_strncmp(delimiter, token->next->str, ft_strlen(token->next->str) + 1) != 0)
				flag_expand = false;
			here_doc(token->next, env, cmd, flag_expand);
			break ;
		}
		token = token->next;
	}
}
