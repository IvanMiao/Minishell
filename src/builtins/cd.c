/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:25:44 by ymiao             #+#    #+#             */
/*   Updated: 2025/03/31 01:43:08 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	ft_cd(char *path)
{
	int	i;

	i = chdir(path);
	if (i != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

/* test */
/*
int	main(int ac, char **av)
{
	char	*path;

	while (1)
	{
		path = readline("minishell$ ");
		if (strncmp(path, "cd ", 3) == 0)
			ft_cd(path + 3);
		getcwd(cwd, sizeof(cwd));
		if (strncmp(path, "stop", 4) == 0)
			return (0);
	}
	return (0);
}
*/