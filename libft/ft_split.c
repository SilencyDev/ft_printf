/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:10:09 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/30 15:16:50 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			is_charset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

int			ft_countword(char *str, char charset)
{
	int		i;

	i = 0;
	while (*str)
	{
		while (is_charset(*str, charset) && *str)
			str++;
		if (!is_charset(*str, charset) && *str)
		{
			while (!is_charset(*str, charset) && *str)
				str++;
			i++;
		}
	}
	return (i);
}

void		ft_str_cpy(char *start, char *str, char *dest)
{
	int		j;

	j = 0;
	while (start < str)
		dest[j++] = *start++;
	dest[j] = '\0';
}

char		**ft_split(char const *s, char c)
{
	char	**dest;
	char	*start;
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!s)
		return (NULL);
	if (!(dest = malloc(sizeof(char *) * (ft_countword(str, c) + 1))))
		return (NULL);
	while (*str)
		if (!is_charset(*str, c))
		{
			start = str;
			while (*str && !is_charset(*str, c))
				str++;
			dest[i] = malloc(str - start + 1);
			ft_str_cpy(start, str, dest[i]);
			i++;
		}
		else
			str++;
	dest[i] = NULL;
	return (dest);
}
