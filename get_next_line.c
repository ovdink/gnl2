/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgendry <sgendry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:20:07 by sgendry           #+#    #+#             */
/*   Updated: 2018/12/16 18:13:54 by sgendry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int			ft_cut(t_file *file, char **line)
{
	char			*start;
	char			*tail;
	int				i;

	file->read_res = 0;
	i = 0;
	start = file->tail;
	if (*(file->tail) == '\n')
	{
		file->tail++;
		tail = ft_strdup(file->tail);
		file->tail = tail;
		ft_strdel(&start);
		*line = ft_strnew(0);
		if (*(file->tail) == '\0' && !(file->read_res))
			file->tail = 0x0;
		return (1);
	}
	while (*(file->tail + i) != '\n' && *(file->tail + i))
		i++;
	//printf("------ %d ---------", i);
	file->tail = file->tail + i + (*(file->tail + i) == '\n');
	//printf(" %s \n", file->tail);
	tail = ft_strdup(file->tail);
	file->tail = tail;
	tail = ft_strsub(start, 0, i);
	//printf("%s\n", tail);
	ft_strdel(&start);
	*line = tail;
	if (*(file->tail) == '\0' && !(file->read_res))
		file->tail = 0x0;
	return (1);
}

static t_file		*create_file(int fd)
{
	t_file			*new_lst;

	new_lst = (t_file *)malloc(sizeof(t_file));
	new_lst->fd = fd;
	new_lst->read_res = 0;
///	new_lst->tail = ft_strnew(BUFF_SIZE);
	new_lst->tail = ft_strnew(0);
	return (new_lst);
}

static t_file		*find_fd(t_file **lst, int fd)
{
	t_file			*iter;
	t_file			*file;

	iter = *lst;
	if (!(lst) || !(*lst))
	{
		file = create_file(fd);
		*lst = file;
	}
	else
	{
		if (iter->fd == fd)
			return (iter);
		while (iter->next)
		{
			if (iter->fd == fd)
				return (iter);
			iter = (iter)->next;
		}
		file = create_file(fd);
		iter->next = file;
	}
	return (file);
}

static void			read_more(t_file *file)
{
	char			*more_temp;
	char			*new_str;

	more_temp = ft_strnew(BUFF_SIZE);
	file->read_res = read(file->fd, more_temp, BUFF_SIZE);
	new_str = ft_strjoin(file->tail, more_temp);
	ft_strdel(&more_temp);
	ft_strdel(&(file->tail));
	file->tail = new_str;
	//if (!ft_strchr(file->tail, '\n') && file->read_res == BUFF_SIZE)
	if (!ft_strchr(file->tail, '\n') && file->read_res)
		read_more(file);
}

int					get_next_line(const int fd, char **line)
{
	static t_file	*list = NULL;
	t_file			*file;

	if (fd < 0 || !line || read(fd, *line, 0) < 0)
		return (-1);
	file = find_fd(&list, fd);
	if (file->read_res == 0 && !(file->tail))
		return (0);
	if (!ft_strchr(file->tail, '\n'))
		read_more(file);
	if (file->tail)
	{
		return(ft_cut(file, line));
	}
//		*line = ft_strdup(file->tail);
//		ft_strdel(&(file->tail));
//		return (1);
//	}
//	if (file->read_res == 0)
	return (0);
//	return (ft_cut(file, line));
}
