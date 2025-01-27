/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:18:11 by sydubois          #+#    #+#             */
/*   Updated: 2024/12/04 15:05:46 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char		*c;
	size_t		i;
	size_t		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		i = ft_strlen(s1);
	j = 0;
	if (s2 != NULL)
		j = ft_strlen(s2);
	c = (char *) malloc(sizeof(char) * (i + j + 1));
	if (c == NULL)
		return (NULL);
	c[i + j] = '\0';
	while (j-- > 0)
		c[i + j] = s2[j];
	while (i-- > 0)
		c[i] = s1[i];
	free(s1);
	free(s2);
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*c;

	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	c = malloc(sizeof(char) * (len + 1));
	if (c == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && s[i])
		c[j++] = s[i++];
	c[j] = '\0';
	return (c);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	chr_start(char *s, char c)
{
	int	i;

	if (s == NULL)
		return (-2);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i + 1);
	return (-1);
}

int	chr_rest(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
	{
		while (s[i] != '\0')
		{
			i++;
			j++;
		}
		return (j);
	}
	else
		return (-1);
}
