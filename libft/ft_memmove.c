/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:11:16 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/27 11:38:22 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	*lasts;
	unsigned char	*lastd;

	d = (unsigned char	*)dest;
	s = (unsigned char	*)src;
	if (d < s)
		return (ft_memcpy(dest, src, n));
	else
	{
		lasts = s + (n - 1);
		lastd = d + (n - 1);
		while (n-- && (dest || src))
			*lastd-- = *lasts--;
	}
	return (dest);
}
