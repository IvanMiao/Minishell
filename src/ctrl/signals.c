/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 04:14:36 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/15 15:13:54 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/*
/-On commence une nouvelle ligne
/-On efface la ligne pour la remplacer par ""
/-On actualise l'invite de commande
*/
void	ctrl_c(int code)
{
	(void)code;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d(char *s, t_env *env)
{
	if (s == NULL)
	{
		printf("exit\n");
		env_free(env);
		exit(0);
	}
}

/*
//SIGINT = Ctrl C
//SIGQUIT = Ctrl -\
//SIG_IGN indique que le signal doit etre ignore
*/
void	controls(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

/*
// Ctrl D = add a EOF to stdin
// if only a EOF in this line, show "exit" and exit
// otherwise, do nothing
*/
/*
int	main(void)
{
    char *s;

	controls();
	while (1)
	{
		s = readline("MINISHELL$ ");
		ctrl_d(s);
		add_history(s);
		printf("GET INPUT: %s\n", s);
	}
    return (0);
}
*/