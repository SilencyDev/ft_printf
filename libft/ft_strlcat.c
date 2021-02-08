/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:56:58 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/23 13:34:25 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	catinc;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	catinc = 0;
	while ((dstlen + catinc) < dstsize - 1 && src[catinc])
	{
		dst[dstlen + catinc] = src[catinc];
		catinc++;
	}
	dst[dstlen + catinc] = '\0';
	return (dstlen + srclen);
}
