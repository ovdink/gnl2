/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgendry <sgendry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:13:56 by sgendry           #+#    #+#             */
/*   Updated: 2018/12/16 18:15:58 by sgendry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		gnl;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "oiuytrew\n", 9);
	write(fd, "abcdefgh\n", 9);
	write(fd, "ijklmnop\n", 9);
	close(p[1]);
	dup2(out, fd);
	int n = 5;
	while((gnl = get_next_line(p[0], &line)) && n--)
	{
		printf("gnl: %d, str: %s\n", gnl, line);
		free(line);
		line = 0x0;
	}
		printf("gnl: %d, str: %s\n", gnl, line);
}

