/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 12:42:31 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/25 16:27:37 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*dest;
	size_t	j;

	j = count * size;
	if (!(dest = malloc(j)))
		return (NULL);
	ft_bzero(dest, j);
	return (dest);
}
