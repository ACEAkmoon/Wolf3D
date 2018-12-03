/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:57:21 by akrushin          #+#    #+#             */
/*   Updated: 2018/08/27 17:57:22 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_next_line(int fd, int cb, char **str, char **line)
{
	int			i;
	char		*str_tmp;

	i = 0;
	BASE_ERROR(cb < 0);
	RETURN_NULL(!cb && (!str[fd] || !str[fd][i]));
	while (str[fd][i] && str[fd][i] != '\n')
		i++;
	if (!str[fd][i] && (*line = ft_strdup(str[fd])))
		ft_strdel(&str[fd]);
	else if ((*line = ft_strndup(str[fd], i)))
	{
		str_tmp = ft_strdup(str[fd] + ++i);
		free(str[fd]);
		str[fd] = str_tmp;
	}
	else if (cb == BUFF_SIZE)
		return (get_next_line(fd, line));
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int			cb;
	static char	*str_stc[255];
	char		*str_tmp;
	char		buffer[BUFF_SIZE + 1];

	BASE_ERROR(fd < 0 || !line || BUFF_SIZE <= 0);
	while ((cb = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[cb] = '\0';
		str_stc[fd] ? str_stc[fd] : (str_stc[fd] = ft_strnew(0));
		str_tmp = ft_strjoin(str_stc[fd], buffer);
		free(str_stc[fd]);
		str_stc[fd] = str_tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (ft_next_line(fd, cb, str_stc, line));
}
