/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:16:03 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/07 03:54:44 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/src.h"

int	main(int argc, char **argv, char **envp)
{
	char	*history;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = set_env(envp);
		//init
	while (1)
	{
		history = readline("minishell >");
		if (!history)
			return (perror("the program launch failed"), 1);
		add_history(history);
		if (ft_strncmp(history, "clear", 5) == 0)
			rl_clear_history();
		if (ft_strncmp(history, "exit", 4) == 0)
			return (free(history), 1);
		if (!strncmp(history, "getenv ", 7))
			printf(GREEN"get env_var!\nname: %s\nword: %s\n"ENDCOLOR, history+7, ft_get_env(env, history+7));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//free
	}
	rl_clear_history();
	//free
	return (0);
}
