/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_supp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 08:39:36 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/14 02:52:44 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	first_write(int fd)
{
	write(fd, "{\n", 2);
	write(fd, "   Readline_memory\n", 19);
	write(fd, "   Memcheck:Leak\n", 17);
	write(fd, "   match-leak-kinds: reachable\n", 31);
	write(fd, "   ...\n", 7);
	write(fd, "   obj:*/libreadline.so*\n", 25);
	write(fd, "}\n\n", 3);
}

int	main(void)
{
	int	fd;

	fd = open("readline.supp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error: Could not create  file\n");
		return (1);
	}
	first_write(fd);
	close(fd);
	return (0);
}
