/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 02:10:55 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/12/09 04:58:18 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_merge(int *src, int left, int right, int *tmp)
{
	int mid;
	int l_idx;
	int r_idx;

	mid = (left + right) / 2;
	if (left < mid)
	{
		ft_merge(src, left, mid, tmp);
		ft_merge(src, mid + 1, right, tmp);
	}
	l_idx = left;
	r_idx = mid + 1;
	while (l_idx <= mid || r_idx <= right)
		if (l_idx <= mid && (r_idx > right || src[l_idx] < src[r_idx]))
			*tmp++ = src[l_idx++];
		else
			*tmp++ = src[r_idx++];
	while (--r_idx >= left)
		src[r_idx] = *--tmp;
}
