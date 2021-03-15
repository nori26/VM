/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:51:45 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 08:40:57 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_idlst		*ft_lstadd_front_o(t_idlst **lst, t_idlst *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_clist		*ft_lstadd_front_c(t_clist **lst, t_clist *new)
{
	if (*lst && new)
	{
		new->next = *lst;
		new->prev = (*lst)->prev;
		(*lst)->prev = new;
	}
	else if (!*lst && new)
		new->prev = new;
	if (new)
		new->prev->next = new;
	*lst = new;
	return (new);
}

t_llist		*ft_lstadd_front_l(t_llist **lst, t_llist *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}
