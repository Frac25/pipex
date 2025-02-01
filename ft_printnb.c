/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42Lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:40:26 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/01 09:52:17 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

int	ft_putnbr(int n, int j)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		j = 11;
	}
	else
	{
		if (n < 0)
		{
			n = -n;
			j += ft_putchar('-');
		}
		if (n >= 10)
			j += ft_putnbr(n / 10, 0);
		n = n % 10;
		if (n < 10)
			j += ft_putchar(n + 48);
	}
	return (j);
}

int	ft_putnbr_ui(unsigned int n, int j)
{
	if (n >= 10)
		j += ft_putnbr(n / 10, 0);
	n = n % 10;
	if (n < 10)
		j += ft_putchar(n + 48);
	return (j);
}

int	ft_putbase(unsigned long n, char *b, int j)
{
	unsigned long	sb;

	sb = ft_strlen(b);
	if (n >= sb)
		j += ft_putbase(n / sb, b, 0);
	n = n % sb;
	if (n <= sb)
	{
		write(1, &b[n], 1);
		j++;
	}
	return (j);
}

int	ft_putbase_ui(unsigned int n, char *b, int j)
{
	unsigned int	sb;

	sb = ft_strlen(b);
	if (n >= sb)
		j += ft_putbase_ui(n / sb, b, 0);
	n = n % sb;
	if (n <= sb)
	{
		write(1, &b[n], 1);
		j++;
	}
	return (j);
}
