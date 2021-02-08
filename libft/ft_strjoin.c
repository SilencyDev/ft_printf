/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:29:32 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/25 15:54:16 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		len;
	char	*dest_init;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = malloc(sizeof(char *) * len + 1)))
		return (NULL);
	dest_init = dest;
	while (*(char *)s1)
		*dest++ = *(char *)s1++;
	while (*(char *)s2)
		*dest++ = *(char *)s2++;
	*dest = '\0';
	return (dest_init);
}
