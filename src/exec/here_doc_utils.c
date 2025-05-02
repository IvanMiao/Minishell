/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:47:29 by cgerner           #+#    #+#             */
/*   Updated: 2025/05/02 04:15:42 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

bool	print_ctrld_hd(char *s)
{
	if (s)
	{
		ft_fprintf(2, "minishell: warning: here-document", NULL);
		ft_fprintf(2," delimited by end-of-file (wanted `%s')\n", s);
	}
	return (true);
}
