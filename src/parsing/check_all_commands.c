/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:31:09 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/11 20:31:30 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	check_all_commands(t_token *token)
{
	return (check_command_in(token) || check_command_out(token)
		|| check_command_delimiter(token) || check_command_redirection(token)
		|| check_command(token));
}
