/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:16:03 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/16 05:40:16 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/src.h"

int	empty_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i == ft_strlen(str));
}

int	check_main(t_token **token, char *history)
{
	if (!*token || empty_line(history))
	{
		if (*token)
			token_lstclear(token);
		free(history);
		return (1);
	}
	if (check_syntax(*token))
	{
		token_lstclear(token);
		free(history);
		return (1);
	}
	return (0);
}

int	exit_history(int value)
{
	rl_clear_history();
	return (value);
}

int	main(int argc, char **argv, char **envp)
{
	char	*history;
	t_env	*env;
	t_token	*token;
	t_shell	shell;

	if (argc != 1)
		return(ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	controls();
	env = set_env(envp);
	(&shell)->env = env;
	while (1)
	{
		history = readline("minishell$ ");
		if (!history)
			exit_history(1);
		ctrl_d(history, env);
		add_history(history);
		(&shell)->str = history;
		token = init_tokens(&shell);
		if (check_main(&token, history))
			continue ;
		(&shell)->exit_code = pipex(token, env);
		token_lstclear(&token);
		free(history);
	}
	env_free(env);
	return (0);
}
