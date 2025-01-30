/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42Lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:54:36 by sydubois          #+#    #+#             */
/*   Updated: 2025/01/28 19:06:12 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int	check_free_all(char **s, size_t size)
{
	if (s[size] == NULL)
	{
		while (size > 0)
			free(s[--size]);
		free (s);
		return (0);
	}
	return (1);
}

void	*ft_malcol(const char *s, char c)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	p = malloc(sizeof(char *) * (j + 1));
	if (p == NULL)
		return (NULL);
	return (p);
}

void	*ft_mallin(const char *s, size_t end)
{
	size_t	i;
	char	*p;

	i = 0;
	p = malloc(sizeof(char) * (end + 1));
	if (p == NULL)
		return (NULL);
	while (i < end)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = ft_malcol(s, c);
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i > 0)
			tab[j] = ft_mallin(s, i);
		if (i > 0)
			if (check_free_all(tab, j++) == 0)
				return (NULL);
		s = s + i;
	}
	tab[j] = NULL;
	return (tab);
}
