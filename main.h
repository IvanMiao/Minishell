/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 05:06:35 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/15 05:15:06 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "src/src.h"

typedef struct	s_shell
{
	char	*history;
	t_token	*token;
	t_env	*env;
	t_cmd	*cmd;
	int		exit_code;
}		t_shell;

#endif