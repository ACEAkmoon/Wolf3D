/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:23:04 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/05 19:23:06 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_clr		ft_set_color(t_img *img, t_clr clr, t_cst cst, double adjust)
{
	t_clr	c1;

	c1 = (t_clr)*(int *)(img->ptr + ((cst.mx + cst.my * img->width) * \
		img->bt_px));
	c1.argb.a = (char)0x00;
	c1.argb.r = c1.argb.r + (clr.argb.r - c1.argb.r) * adjust;
	c1.argb.g = c1.argb.g + (clr.argb.g - c1.argb.g) * adjust;
	c1.argb.b = c1.argb.b + (clr.argb.b - c1.argb.b) * adjust;
	return (c1);
}
