/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 04:11:35 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 09:02:06 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**free_all(char ***ret)
{
	size_t i;

	if (!*ret || !ret)
		return (NULL);
	i = 0;
	while ((*ret)[i])
	{
		free((*ret)[i]);
		(*ret)[i++] = 0;
	}
	free(*ret);
	return (*ret = NULL);
}
