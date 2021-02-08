/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:37:38 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/25 14:04:51 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_intlen(long int n)
{
	int			len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

long int		ft_noneg(long int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char			*ft_itoa(int n)
{
	char		*dst;
	int			len;
	int			neg;

	len = ft_intlen(n);
	neg = (n < 0) ? -1 : 1;
	if (!(dst = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dst[len--] = '\0';
	while (len >= 0)
	{
		dst[len] = '0' + ft_noneg(n % 10);
		n = ft_noneg(n / 10);
		len--;
	}
	if (neg == -1)
		dst[0] = '-';
	return (dst);
}
