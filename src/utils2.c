/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:28:09 by kmacquet          #+#    #+#             */
/*   Updated: 2021/02/17 11:48:50 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_option	*ft_init_option(t_option *o)
{
	o->flag_minus = 0;
	o->flag_zero = 0;
	o->width = 0;
	o->dot = -1;
	o->a_p = 0;
	o->type = 0;
	return (o);
}

int			padding(int i, char c)
{
	int	j;

	j = 0;
	while (i-- > 0)
		j += ft_putchar(c, 1);
	return (j);
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
