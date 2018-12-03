/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:28:15 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/27 17:29:05 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstrev(t_list **alst)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	prev = NULL;
	curr = *alst;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*alst = prev;
	return (*alst);
}
