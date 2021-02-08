/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:14:00 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/25 15:55:21 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ischarset(char c, char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	char	*src;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1) - 1;
	src = (char *)s1;
	while (*src && ft_ischarset(src[end], (char *)set))
		end--;
	while (*src && ft_ischarset(src[start], (char *)set))
		start++;
	if (!(dest = malloc((start > end ? start : end) - start + 1)))
		return (NULL);
	while (end >= start)
		dest[i++] = src[start++];
	dest[i] = '\0';
	return (dest);
}
