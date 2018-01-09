/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlyubich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:05:46 by dlyubich          #+#    #+#             */
/*   Updated: 2018/01/09 15:05:47 by dlyubich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	str = (char*)malloc((len + 1) * sizeof(char));
	if (str == NULL || !s)
		return (NULL);
	while (s[i] && i != start)
		i++;
	if (i == start)
	{
		while (j < len)
			str[j++] = s[i++];
		str[j] = '\0';
		return (str);
	}
	return (0);
}

int					ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
