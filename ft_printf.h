/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42Lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:08:40 by sydubois          #+#    #+#             */
/*   Updated: 2024/11/06 12:03:48 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <ctype.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putptr(unsigned long n);
int		ft_print_type(va_list args, char format);
size_t	ft_strlen(const char *s);
int		ft_putnbr(int n, int j);
int		ft_putnbr_ui(unsigned int n, int j);
int		ft_putbase(unsigned long n, char *b, int j);
int		ft_putbase_ui(unsigned int n, char *b, int j);

#endif
