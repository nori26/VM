/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 06:00:44 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/19 17:16:11 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!lst || !del || !*lst)
		return ;
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next), del);
	ft_lstdelone(*lst, del);
	*lst = 0;
}
