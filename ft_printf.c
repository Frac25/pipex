/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42Lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:50:32 by sydubois          #+#    #+#             */
/*   Updated: 2024/11/06 12:00:27 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i += ft_putchar(s[i]);
	return (i);
}

int	ft_putptr(unsigned long n)
{
	int	i;

	write (1, "0", 1);
	write (1, "x", 1);
	i = 2 + ft_putbase(n, "0123456789abcdef", 0);
	return (i);
}

int	ft_print_type(va_list args, char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_putchar(va_arg(args, int));
	if (format == 'i')
		i += ft_putnbr(va_arg(args, int), 0);
	if (format == 's')
		i += ft_putstr(va_arg(args, char *));
	if (format == 'p')
		i += ft_putptr((unsigned long)va_arg(args, char *));
	if (format == 'x')
		i += ft_putbase_ui(va_arg(args, int), "0123456789abcdef", 0);
	if (format == 'X')
		i += ft_putbase_ui(va_arg(args, int), "0123456789ABCDEF", 0);
	if (format == 'd')
		i += ft_putnbr(va_arg(args, int), 0);
	if (format == 'u')
		i += ft_putnbr_ui((unsigned int)va_arg(args, unsigned int), 0);
	if (format == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *str, ...)
{
	char		sep;
	size_t		i;
	int			j;
	va_list		args;

	va_start(args, str);
	sep = '%';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			i++;
			j += ft_print_type(args, str[i]);
		}
		else
			j += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (j);
}
/*
int	main(void)
{
	char			t1 = '1'; //%c
	int				t2 = 2; // %i
	char			*t3 = "trois";//%s
	char			*t4 = "4"; //%p
	int				t5 = -2650; //%x
	int				t6 = 2666; //%X
	int				t7 = -777; //%d
	unsigned int	t8 = 4294967295; //%u

	ft_printf("t0 : pas d'arguments et pourcent \n");
	printf("   t01 : %d\n", ft_printf("12345"));
	printf("   t02 : %d\n", ft_printf("1%%4"));
	printf("   t03 : %d\n", ft_printf("%%"));
	printf("   t04 : %d\n\n", ft_printf("%%%%"));

	ft_printf("t1 : char c : %c\n", t1);
	printf("   t11 : %d\n\n", ft_printf("%%%c", t1));

	ft_printf("t2 : integer b10 i : %i\n\n", t2);

	ft_printf("t3 : string b10 s : %s\n, pointer : %p", t3);
	printf("   t31 : %d\n", ft_printf("%s", t3));
	printf("   t32 : %d\n\n", ft_printf("%s", (char *)NULL));

	ft_printf("t4 : pointer p : %p\n", t4);
	printf("   t41 : %d\n\n", ft_printf("%p", t4));

	ft_printf("t5 : hexa x : %x\n", t5);
	printf("   t51 : %d\n\n", ft_printf("%x", t5));

	ft_printf("t6 : HEXA X : %X\n\n", t6);

	ft_printf("t7 : decimal b10 d: %d\n", t7);
	printf("   t71 : %d\n\n", ft_printf("%d", t7));

	ft_printf("t8 : unsigned int u : %u\n\n", t8);

	return (0);
}
*/
