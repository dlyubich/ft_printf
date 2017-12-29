#include "ft_printf.h"

void	ft_help(t_val val)
{
	char *str;

	if (val.bukva == '\0')
		return ;
	else if (val.width <= 0)
		g_count += write(1, &val.bukva, 1);
	else
	{
		str = ft_strnew(val.width);
		if (val.zero > 0)
			ft_memset(str, '0', val.width);
		else
			ft_memset(str, ' ', val.width);
		if (val.minus > 0)
			str[0] = val.bukva;
		else
			str[val.width - 1] = val.bukva;
		g_count += write(1, str, val.width);
		free(str);
	}
}

void	ft_bminone(void *s, size_t n)
{
	unsigned long i;
	unsigned char *new;

	i = 0;
	new = (unsigned char*)s;
	while (i < n)
	{
		new[i] = 0;
		i++;
	}
}

int   count_char(const char *str, int i, t_val *val, char c)
{
  int counter;

  counter = 0;
  while (str[i] == c)
  {
    counter++;
    i++;
  }
  if (counter % 2)
    val->size = c == 'l' ? 3 : 2;
  else
    val->size = c == 'l' ? 4 : 1;
  return (i - 1);
}

int   parse_args(const char *str, int i, va_list args)
{
  t_val val;
  int tmp;

  ft_bminone(&val, sizeof(val));
  val.prec = -1;
  while (1)
  {
		tmp = i;
	  while (str[i] == '-' || str[i] == '+' || str[i] == '0' || str[i] == '#' || str[i] == ' ')
	  {
	    if (str[i] == '-' && !(val.zero = 0))
	      val.minus = 1;
	    else if (str[i] == '+')
	      val.sign = 1;
	    else if (str[i] == '0' && !val.minus)
	      val.zero = 1;
	    else if (str[i] == '#')
	      val.resh = 1;
	    else if (str[i] == ' ' && val.sign != 1)
	      val.space = 1;
	    i++;
	  }
	  while (ft_isdigit(str[i]))
	  {
	    val.width = val.width * 10 + str[i] - '0';
	    i++;
	  }
	  if (str[i] == '.' && ft_isdigit(str[i + 1]) && (i += 1))
	  {
	  	val.prec = 0;
	    while (ft_isdigit(str[i]))
	    {
	      val.prec = val.prec * 10 + str[i] - '0';
	     i++;
	    }
	  }
	  else if (str[i] == '.')
	  {
	  	val.prec = 0;
	  	i++;
	  }
	  while (str[i] == 'j' || str[i] == 'l' || str[i] == 'h' || str[i] == 'z')
	  {
	    if (str[i] == 'z')
	      val.size = 6;
	    else if (str[i] == 'j' && val.size < 5)
	      val.size = 5;
	    else if (str[i] == 'l' && val.size < 4)
	      i = count_char(str, i, &val, 'l');
	    else if (str[i] == 'h' && val.size < 2)
	      i = count_char(str, i, &val, 'h');
	    i++;
	  }
	  if (tmp == i)
	  	break;
	}
  val.bukva = str[i];
  if (val.bukva == 's' || val.bukva == 'S' || val.bukva == 'o' || val.bukva == 'O' 
  	|| val.bukva == 'u' || val.bukva == 'U' || val.bukva == 'd' || val.bukva == 'D' || val.bukva == 'i'
  	|| val.bukva == 'x' || val.bukva == 'X' || val.bukva == 'c' || val.bukva == 'C')
  	ft_cast(val, args);
  else
  	ft_help(val);
  if (!str[i])
  	return (i);
  return (i + 1);
}

static int ft_my_printf(const char *str, va_list args) 
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%' && (i += 2))
				g_count += write(1, "%", 1);
			else
				i = parse_args(str, ++i, args);
		}
		else
		{
			g_count += write(1, &str[i], 1);
			i++;
		}
	}
	return (g_count);
}  

int       ft_printf(const char *format, ...)
{
  va_list args;
  int   res;

  va_start(args, format);
  g_count = 0;
  res = ft_my_printf(format, args);
  va_end(args);
  return (res);
}   
     
