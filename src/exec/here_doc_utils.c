/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:47:29 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/24 10:20:48 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

bool	print_ctrld_hd(char *s)
{
	if (s)
	{
		printf("minishell: warning: here-document");
		printf(" delimited by end-of-file (wanted `%s')\n", s);
	}
	return (true);
}
