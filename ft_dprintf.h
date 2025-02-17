/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:08:40 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/17 11:53:46 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <ctype.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_dprintf(int fd, const char *str, ...);
int		ft_dputchar(int fd, char c);
int		ft_dputstr(int fd, char *s);
int		ft_dputptr(int fd, unsigned long n);
int		ft_dprint_type(int fd, va_list args, char format);
size_t	ft_strlen(const char *s);
int		ft_dputnbr(int fd, int n, int j);
int		ft_dputnbr_ui(int fd, unsigned int n, int j);
int		ft_dputbase(int fd, unsigned long n, char *b, int j);
int		ft_dputbase_ui(int fd, unsigned int n, char *b, int j);

#endif
