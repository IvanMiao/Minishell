/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 04:14:36 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/18 15:11:23 by ymiao            ###   ########.fr       */
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
	signal(SIGINT, ctrl_c); // doute
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