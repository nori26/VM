/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 20:15:52 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/19 20:33:35 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *ret;
	t_list *next;

	next = 0;
	if (!f || !lst || (lst->next && !(next = ft_lstmap(lst->next, f, del))))
		return (NULL);
	if (!(ret = ft_lstnew(f(lst->content))))
		ft_lstclear(&next, del);
	if (ret)
		ret->next = next;
	return (ret);
}
