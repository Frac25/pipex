/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:22:17 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/17 12:56:21 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_same_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s2[i] != '\0')
		return (-1);
	return (1);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*c1;
	const unsigned char	*c2;
	size_t				i;

	c1 = (const unsigned char *)s1;
	c2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (c1[i] != c2[i])
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}

int	cpy(char *c, char const *s1, int i)
{
	c[i] = s1[i];
	i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	i = 0;
	while (t1[i] == t2[i] && t1[i] && t2[i])
		i++;
	return (t1[i] - t2[i]);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*c;
	size_t	i;
	size_t	j;
	int		l;

	l = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (s1 && s2)
	{
		c = malloc(sizeof(char) * l + 1);
		if (c == NULL)
			return (NULL);
		i = 0;
		while (i < ft_strlen(s1))
			i = cpy(c, s1, i);
		j = 0;
		while (j < ft_strlen(s2))
			c[i++] = s2[j++];
		j = 0;
		while (j < ft_strlen(s3))
			c[i++] = s3[j++];
		c[i] = '\0';
		return (c);
	}
	return (NULL);
}
