/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:16:20 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 16:16:21 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_take_wlen(const uint32_t symbol)
{
	int			size;

	size = 0;
	if (symbol <= BIT7)
		size += 1;
	else if (symbol <= BIT11)
		size += 2;
	else if (symbol <= BIT16)
		size += 3;
	else if (symbol <= BIT21)
		size += 4;
	return (size);
}

char			*ft_parse_wchar(const uint32_t symbol, int p)
{
	char		*rt;

	rt = ft_strnew(4);
	if (symbol <= BIT7 && p >= 1)
		rt[0] = symbol;
	else if (symbol <= BIT11 && p >= 2)
	{
		rt[0] = ((symbol & 1984) >> 6) | 192;
		rt[1] = (symbol & 63) | 128;
	}
	else if (symbol <= BIT16 && p >= 3)
	{
		rt[0] = ((symbol & 61440) >> 12) | 224;
		rt[1] = ((symbol & 4032) >> 6) | 128;
		rt[2] = (symbol & 63) | 128;
	}
	else if (symbol <= BIT21 && p >= 4)
	{
		rt[0] = ((symbol & 1835008) >> 18) | 240;
		rt[1] = ((symbol & 258048) >> 12) | 128;
		rt[2] = ((symbol & 4032) >> 6) | 128;
		rt[3] = (symbol & 63) | 128;
	}
	return (rt);
}

void			ft_make_width(char **data, t_val val)
{
	int i;

	i = 0;
	if (val.minus == 1)
	{
		ft_wputstr(data);
		ft_place_char(val.width - ft_check_len_wch(data), ' ');
	}
	else if (val.zero == 1)
	{
		ft_place_char(val.width - ft_check_len_wch(data), '0');
		ft_wputstr(data);
	}
	else
	{
		ft_place_char(val.width - ft_check_len_wch(data), ' ');
		ft_wputstr(data);
	}
	while (data[i])
		free(data[i++]);
	free(data);
}

void			ft_widestr(wchar_t *d, t_val val)
{
	int			i;
	int			p;
	char		**s;

	i = 0;
	while (d[i])
		i++;
	s = (char**)malloc(sizeof(char*) * (i + 1));
	s[i] = NULL;
	i = 0;
	p = val.prec;
	while (d[i])
	{
		if (val.prec < 0)
			p = 4;
		s[i] = ft_parse_wchar(d[i], p);
		p -= ft_take_wlen(d[i]);
		i++;
	}
	ft_make_width(s, val);
}
