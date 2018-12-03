/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:55:32 by akrushin          #+#    #+#             */
/*   Updated: 2018/08/27 17:55:34 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include "libft.h"

# define BUFF_SIZE 10

# define BASE_ERROR(x) if (x) return (-1);
# define RETURN_NULL(x) if (x) return (0);

int		get_next_line(const int fd, char **line);
#endif
