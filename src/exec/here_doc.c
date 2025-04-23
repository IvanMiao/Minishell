/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/23 18:14:21 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int g_signal_received;


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

void	read_expand(int fd, char *str, bool flag_expand, t_env *env)
{
	char	*result_expand;

	if (flag_expand)
	{
		result_expand = heredoc_expand(str, env);
		ft_fprintf(fd, "%s\n", result_expand);
		free(result_expand);
	}
	else
		ft_fprintf(fd, "%s\n", str);
}

void	read_here_doc(char *delimiter, bool flag_expand, t_env *env, t_cmd *cmd)
{
	char	*str;

	cmd->fd = open("./.heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd < 0)
		return ;
	while (1)
	{
		str = readline("> ");
		if (g_signal_received == 1)
		{
			if (cmd->fd >= 0)
				close(cmd->fd);
			printf("signal recevied!\n");
			free_all(env, NULL, cmd);
			exit(130);
		}
		if (!str)
		{
			print_ctrld_hd(delimiter);
			break ;
		}
		if ((ft_strlen(str) == ft_strlen(delimiter)
				&& ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0))
			break ;
		read_expand(cmd->fd, str, flag_expand, env);
		free(str);
	}
	close(cmd->fd);
	free(str);
}

void	ctrl_c_hd(int code)
{
	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_received = 1;
}

void	handle_child_process(t_cmd *cmd, t_env *env)
{
	int		i;
	bool	flag_expand;
	char	*delimiter;

	i = 0;
	signal(SIGINT, ctrl_c_hd);
	while (cmd->delimiter[i])
	{
		flag_expand = true;
		delimiter = remove_quotes(cmd->delimiter[i]);
		if (ft_strncmp(delimiter, cmd->delimiter[i]
				, ft_strlen(cmd->delimiter[i]) + 1) != 0)
			flag_expand = false;
		read_here_doc(delimiter, flag_expand, env, cmd);
		free(delimiter);
		i++;
	}
}
