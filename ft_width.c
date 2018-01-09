/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:41:50 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 14:41:51 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_width_help(char **str, t_val val, int len)
{
	char	*tmp;
	char	*buf;

	tmp = ft_strnew(val.width - len);
	ft_memset(tmp, ' ', val.width - len);
	buf = *str;
	if (val.minus > 0)
		*str = ft_strjoin(*str, tmp);
	else
		*str = ft_strjoin(tmp, *str);
	free(tmp);
	free(buf);
}

char	*ft_width(char *str, t_val val)
{
	int		len;
	int		tm;

	if ((len = ft_strlen(str)) < val.width)
	{
		if (val.prec < 0 && val.minus != 1 && val.zero == 1)
		{
			if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
				val.width -= 1;
			if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
				val.width -= 2;
			tm = val.prec;
			val.prec = val.width;
			str = ft_mod_prec(str, val);
			val.prec = tm;
			return (str);
		}
		else
			ft_width_help(&str, val, len);
	}
	return (str);
}
