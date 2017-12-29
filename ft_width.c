#include "ft_printf.h"

char	*ft_width(char *str, t_val val)
{
	char *tmp;
	int len;
	char *buf;
	int tm;

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
		{
			tmp = ft_strnew(val.width - len);
			ft_memset(tmp, ' ', val.width - len);
			buf = str;
			if (val.minus > 0)
				str = ft_strjoin(str, tmp);
			else
				str = ft_strjoin(tmp, str);
		}
		free(tmp);
		free(buf);
	}
	return (str);
}
