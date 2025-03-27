/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:25:44 by ymiao             #+#    #+#             */
/*   Updated: 2025/03/27 03:08:11 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_cd(char *path)
{
	int i = chdir(path);
	printf("%d\n", i);
	if (i != 0)
		return (1);
	printf("path changed\n");
	return(0);
}

/*
 test
*/
int	main(int ac, char **av)
{
	char cwd[1024];
	char *path;
	
	getcwd(cwd, sizeof(cwd));
	while (1)
	{
		printf("minishell: %s", cwd);
		path = readline("$ ");
		if (strncmp(path, "cd ", 3) == 0)
			ft_cd(path+3);
		getcwd(cwd, sizeof(cwd));
	}
	return (0);
}
