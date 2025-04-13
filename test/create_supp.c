/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_supp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 08:39:36 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/13 18:05:32 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	first_write(int fd)
{
	write(fd, "{\n", 2);
	write(fd, "   Readline_memory\n", 19);
	write(fd, "   Memcheck:Leak\n", 16);
	write(fd, "   match-leak-kinds: reachable\n", 31);
	write(fd, "   ...\n", 6);
	write(fd, "   obj:*/libreadline.so*\n", 25);
	write(fd, "}\n\n", 3);
}

void	second_write(int fd)
{
	write(fd, "{\n", 2);
	write(fd, "   Readline_history_memory\n", 27);
	write(fd, "   Memcheck:Leak\n", 16);
	write(fd, "   match-leak-kinds: reachable\n", 31);
	write(fd, "   ...\n", 6);
	write(fd, "   fun:add_history\n", 19);
	write(fd, "}\n\n", 3);
}

void	third_write(int fd)
{
	write(fd, "{\n", 2);
	write(fd, "   Tinfo_memory\n", 16);
	write(fd, "   Memcheck:Leak\n", 16);
	write(fd, "   match-leak-kinds: reachable\n", 31);
	write(fd, "   ...\n", 6);
	write(fd, "   obj:*/libtinfo.so*\n", 22);
	write(fd, "}\n", 2);
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
	second_write(fd);
	third_write(fd);
	close(fd);
	return (0);
}
