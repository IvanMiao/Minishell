/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/17 21:02:26 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/* expansion of all the dollar vars in char *str! */
/*
static char	*heredoc_expand(char *str, t_env *env)
{
	char	*tmp;
	char	*env_word;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '$')
		i++;
	if (str[i])
		i++;
	j = i;
	if (str[i] && str[i] != '_' && !ft_isalpha(str[i]))
		i++;
	while (str[i] && (str[i] == '_' || ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;

	tmp = ft_substr(str, j, i - j);
	env_word = ft_get_env(env, tmp);
	free(tmp);
	if (!env_word)
		env_word = ft_strdup("");
	tmp = ft_substr(str, 0, j - 1);

}
*/

void	read_here_doc(char *delimiter, bool flag_expand, t_env *env)
{
	char	*str;
	int		fd;

	(void)env; // tmp
	(void)flag_expand; // tmp
	fd = open("./.heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		str = readline("> ");
		//if (flag_expand == true)
		if (ft_strlen(str) == ft_strlen(delimiter)
			&& ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		ft_fprintf(fd, "%s\n", str);
		free(str);
	}
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
		printf("demiliter is : %s\n", delimiter);
		if (ft_strncmp(delimiter, cmd->delimiter, ft_strlen(cmd->delimiter) + 1) != 0)
			flag_expand = false;
		read_here_doc(delimiter, flag_expand, env);
	}
}
