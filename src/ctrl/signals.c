/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 04:14:36 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/22 16:38:28 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

void	ctrl_c(int code)
{
	(void)code;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, ctrl_c);
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

void	controls(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	sig_in_parent(int value)
{
	struct sigaction	sa_ign;
	struct sigaction	sa_int_old;
	struct sigaction	sa_quit_old;

	sa_ign.sa_handler = SIG_IGN;
	sigemptyset(&sa_ign.sa_mask);
	sa_ign.sa_flags = 0;
	sigaction(SIGINT, &sa_ign, &sa_int_old);
	sigaction(SIGQUIT, &sa_ign, &sa_quit_old);
	if (value == 2)
		controls();
}

void	sig_in_child(void)
{
	struct sigaction	sa_dfl;

	sa_dfl.sa_handler = SIG_DFL;
	sigemptyset(&sa_dfl.sa_mask);
	sa_dfl.sa_flags = 0;
	sigaction(SIGINT, &sa_dfl, NULL);
	sigaction(SIGQUIT, &sa_dfl, NULL);
}
