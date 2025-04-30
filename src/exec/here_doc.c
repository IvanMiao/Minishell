/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/30 17:18:36 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

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
	mem_manager(FREE, 0, var_name);
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
		mem_manager(FREE, 0, old);
		mem_manager(FREE, 0, tmp);
	}
	return (result);
}

void	read_expand(int fd, char *str, bool flag_expand, t_env *env)
{
	char	*result_expand;

	if (flag_expand)
	{
		result_expand = heredoc_expand(str, env);
		ft_fprintf(fd, "%s\n", result_expand);
		mem_manager(FREE, 0, result_expand);
	}
	else
		ft_fprintf(fd, "%s\n", str);
}

void	ctrl_c_hd(int code)
{
	(void)code;
	printf("\n");
	g_signal_received = SIGINT;
	close(0);
}

void	read_here_doc(char *delimiter, bool flag_expand, t_env *env, t_cmd *cmd)
{
	char	*str;

	cmd->fd = open("./.heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd < 0)
		return ;
	signal(SIGINT, ctrl_c_hd);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			if (g_signal_received == SIGINT)
				break ;
			print_ctrld_hd(delimiter);
			break ;
		}
		if ((ft_strlen(str) == ft_strlen(delimiter)
				&& ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0))
			break ;
		read_expand(cmd->fd, str, flag_expand, env);
		free(str);
	}
	free(str);
	close(cmd->fd);
}
