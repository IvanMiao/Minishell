/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_part2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:51:42 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/21 16:46:07 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	is_directory(t_cmd *cmd)
{
	struct stat	info;

	if (stat(cmd->pathname, &info) != 0)
		return (0);
	if (S_ISDIR(info.st_mode))
		ft_fprintf(2, "minishell: %s: Is a directory\n", cmd->pathname);
	return (S_ISDIR(info.st_mode));
}

int	file_exist(t_cmd *cmd)
{
	if (ft_strchr(cmd->pathname, '/'))
	{
		if (access(cmd->pathname, X_OK | F_OK))
		{
			ft_fprintf(2, "minishell: ", NULL);
			perror(cmd->pathname);
			return (126);
		}
	}
	return (0);
}
