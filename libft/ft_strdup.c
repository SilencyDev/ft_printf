/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:08:34 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/23 13:29:16 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *string;

	if (!(string = malloc(sizeof(char *) * ft_strlen(s1) + 1)))
		return (NULL);
	ft_strlcpy(string, s1, (size_t)ft_strlen(s1) + 1);
	return (string);
}
