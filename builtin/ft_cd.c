/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:25:44 by ymiao             #+#    #+#             */
/*   Updated: 2025/03/26 19:42:38 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_cd(char *path)
{
	int i = chdir(path);
	printf("%d\n", i);
	if (i != 0)
		return (1);
	printf("change path\n");
	return(0);
}

/* how to test?
int	main(int ac, char **av)
{
	pid_t	f;

	f = fork();
	if (f == 0)
	{
		if (ac > 1)
			ft_cd(av[1]);
	}
	wait(NULL);
	return 0;
}
*/