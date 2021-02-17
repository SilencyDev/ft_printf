/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:11:10 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/17 11:47:55 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_putstr(char *str, int prec, int on)
{
	int	i;

	i = 0;
	if (prec > 0)
		while (*str && str && i < prec)
			i += ft_putchar(*str++, on);
	else if (prec < 0)
		while (*str && str)
			i += ft_putchar(*str++, on);
	return (i);
}

int			ft_strlen(const char *s)
{
	int n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

int			ft_intlen(long int n)
{
	int	len;

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

size_t		len_filter(char *toformat)
{
	size_t	j;

	j = 0;
	while (find_converter(toformat[j], "0123456789.-*") && *toformat)
		j++;
	return (j);
}
