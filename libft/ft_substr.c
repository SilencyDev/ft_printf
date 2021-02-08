/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:39:29 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/24 12:40:19 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s || !(dest = ((int)start >= ft_strlen(s)) ? malloc(1)
		: malloc(len + 1)))
		return (NULL);
	if ((int)start < ft_strlen(s))
		while (s[start] && len--)
			dest[i++] = (char)s[start++];
	dest[i] = '\0';
	return (dest);
}
