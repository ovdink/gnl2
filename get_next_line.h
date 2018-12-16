/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgendry <sgendry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:55:21 by sgendry           #+#    #+#             */
/*   Updated: 2018/12/16 17:49:35 by sgendry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFF_SIZE 	5

typedef struct		s_file
{
	int				fd;
	char			*tail;
	int				read_res;
	struct s_file	*next;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
