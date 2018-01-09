/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:15:38 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 16:15:39 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_wputstr(char **d)
{
	int		a;
	int		j;

	a = 0;
	while (d[a])
	{
		j = 0;
		while (d[a][j])
		{
			g_count += write(1, &d[a][j], 1);
			j++;
		}
		a++;
	}
}

int			ft_check_len_wch(char **data)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (data[i])
	{
		tmp += ft_strlen(data[i]);
		i++;
	}
	return (tmp);
}

void		ft_place_char(int size, char c)
{
	int		i;

	i = 0;
	while (i < size)
	{
		g_count += write(1, &c, 1);
		i++;
	}
}

void		ft_char(t_val val, va_list args)
{
	int			c;
	char		ch;

	ch = ' ';
	c = va_arg(args, int);
	if (val.width > 0)
	{
		if (val.zero == 1)
			ch = '0';
		if (val.minus == 1)
		{
			g_count += write(1, &c, 1);
			ft_place_char(val.width - 1, ch);
		}
		else
		{
			ft_place_char(val.width - 1, ch);
			g_count += write(1, &c, 1);
		}
	}
	else
		g_count += write(1, &c, 1);
}

char		*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
