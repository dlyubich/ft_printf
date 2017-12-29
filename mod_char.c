#include "ft_printf.h"

void	ft_modchar(char *str, t_val val)
{
	char *tmp;
	int len;

	if (val.prec != -1 && val.prec < (int)ft_strlen(str))
	{
		tmp = str;
		str = ft_strsub(str, 0, val.prec);
		free(tmp);
	}
	len = ft_strlen(str);
	if (val.width > len)
	{
		tmp = ft_strnew(val.width - len);
		if (val.zero > 0 && val.space <= 0)
			ft_memset(tmp, '0', val.width - len);
		else
			ft_memset(tmp, ' ', val.width - len);
		if (val.minus > 0)
		{
			g_count += write(1, str, len);
			g_count += write(1, tmp, val.width - len);
		}
		else
		{
			g_count += write(1, tmp, val.width - len);
			g_count += write(1, str, len);
		}
		free(tmp);
	}
	else
		g_count += write(1, str, len);
	free(str);
}