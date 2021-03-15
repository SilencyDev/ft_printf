/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:11:10 by kmacquet          #+#    #+#             */
/*   Updated: 2021/03/15 13:15:54 by kmacquet         ###   ########.fr       */
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

size_t		len_filter(char *toformat)
{
	size_t	j;

	j = 0;
	while (find_converter(toformat[j], "0123456789.-*") && *toformat)
		j++;
	return (j);
}

void	padding(int i, char c)
{
	while (i-- > 0)
		ft_putchar(c, 1);
}

char		*set_base(char c)
{
	if (c == 'p' || c == 'x')
		return ("0123456789abcdef");
	else if (c == 'd' || c == 'i' || c == 'u')
		return ("0123456789");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	return (0);
}
