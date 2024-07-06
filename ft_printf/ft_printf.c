/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:30:48 by lteng             #+#    #+#             */
/*   Updated: 2024/06/03 21:30:40 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end

Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int	ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$

Obs: Your function must not have memory leaks. Moulinette will test that.
*/
//man va_arg

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
		i += write(1, &str[i], 1);
	return (i);
}

int	ft_putnbr(long nbr, int base)
{
	char	*str;
	int		i;

	str = "0123456789abcdef";
	i = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		i += write(1, "-", 1);
	}
	if (nbr >= base)
		i += ft_putnbr(nbr / base, base);
	i += write(1, &str[nbr % base], 1);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 's')
				len += ft_putstr(va_arg(args, char *));
			if (str[i] == 'd')
				len += ft_putnbr(va_arg(args, int), 10);
			if (str[i] == 'x')
				len += ft_putnbr(va_arg(args, unsigned int), 16);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
/*
int	main(void)
{
	printf("%s\n", "hello");
	printf("%d\n", 42);
	printf("%x\n", 42);
}
*/
