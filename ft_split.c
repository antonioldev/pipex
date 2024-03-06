/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:14:59 by alimotta          #+#    #+#             */
/*   Updated: 2024/01/26 07:29:42 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(const char *str, char c)
{
	int	count;
	int	sep;
	int	i;

	count = 0;
	sep = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && sep == 0)
		{
			sep = 1;
			count++;
		}
		else if (str[i] == c)
			sep = 0;
		i++;
	}
	count++;
	return (count);
}

static char	**ft_free(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free (arr[i]);
		i++;
	}
	free (arr);
	return (NULL);
}

static char	*fill_string(const char *str, int *start, int end)
{
	int		start_word;
	int		i;
	char	*word;

	i = 0;
	start_word = *start;
	word = (char *)malloc((end - start_word + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start_word < end)
	{
		word[i] = str[start_word];
		i++;
		start_word++;
	}
	word[i] = '\0';
	*start = -1;
	return (word);
}

static char	**create_array(char *s, char c)
{
	char	**arr;

	arr = malloc(word_count(s, c) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	int		j;
	int		start_w;
	char	**arr;

	arr = create_array((char *)s, c);
	if (!arr)
		return (0);
	i = -1;
	j = 0;
	start_w = -1;
	while (++i <= ft_strlen((char *)s))
	{
		if (s[i] != c && start_w < 0)
			start_w = i;
		else if ((s[i] == c || i == ft_strlen((char *)s)) && start_w >= 0)
		{
			arr[j] = fill_string(s, &start_w, i);
			if (!arr[j])
				return (ft_free(arr, j));
			j++;
		}
	}
	arr[j] = 0;
	return (arr);
}
