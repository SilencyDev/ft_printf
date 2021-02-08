/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:54:10 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/25 11:05:41 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	if (!src)
		return (0);
	while ((char)src[count])
		count++;
	if (dstsize == 0)
		return (count);
	while ((char)src[i] && (i < (dstsize - 1)))
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = '\0';
	return (count);
}
