/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:47:29 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/22 16:56:29 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

bool	print_ctrld_hd(char *s)
{
	if (s)
	{
		printf("minishell: warning: here-document at");
		printf(" line 1 delimited by end-of-file (wanted `%s')\n", s);
	}
	return (true);
}

void	ctrl_c_hd(int code)
{
	(void)code;
	printf("\n");
	exit (130); //TODO
}
