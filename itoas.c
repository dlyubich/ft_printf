/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:52:31 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 15:02:53 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		f_ten(intmax_t value, char *str, intmax_t base, int *i)
{
	char	*tmp;

	tmp = "0123456789ABCDEF";
	if (value <= -base || value >= base)
		f_ten(value / base, str, base, i);
	str[(*i)++] = tmp[A(value % base)];
}

char		*ft_itoaint(intmax_t value)
{
	int				i;
	char			*str;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * 32)))
		return (0);
	if (value < 0)
		str[i++] = '-';
	f_ten(value, str, 10, &i);
	str[i] = '\0';
	return (str);
}

size_t		ft_len_num(unsigned long long value, int base)
{
	int	count;

	count = 0;
	if (value <= 0)
		count++;
	while (value != 0)
	{
		count++;
		value /= base;
	}
	return (count);
}

char		*ft_lower_case(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char		*ft_itoa_base(unsigned long long value, int base, int flag)
{
	char	*itoa;
	char	*box;
	size_t	len;

	box = "0123456789ABCDEF";
	len = ft_len_num(value, base);
	itoa = ft_strnew(len);
	if (itoa)
	{
		itoa[len] = '\0';
		if (value == 0)
			itoa[0] = '0';
		while (value != 0)
		{
			itoa[--len] = box[(value % base)];
			value = value / base;
		}
		if (flag == 0)
			itoa = ft_lower_case(itoa);
	}
	return (itoa);
}
