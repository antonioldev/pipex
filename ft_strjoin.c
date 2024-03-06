/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:01:22 by alimotta          #+#    #+#             */
/*   Updated: 2024/02/01 16:01:24 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**This f() calculate the lenght of the string cmd without OPTIONS
*/
static int	ft_lenght(char *argv)
{
	int	j;

	j = 0;
	while (argv[j] != 32)
	{
		if (argv[j] == '\0' || argv[j] == 32)
			return (j);
		j++;
	}
	return (j);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	sep_len;
	char	*s3;
	char	*sep;

	sep = "/";
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_lenght((char *)s2);
	sep_len = ft_strlen((char *)sep);
	s3 = (char *)malloc((s1_len + s2_len) * sizeof(char) + 2);
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, s1_len + 1);
	ft_strlcat(s3, sep, s1_len + sep_len + 1);
	ft_strlcat(s3, s2, s1_len + sep_len + s2_len + 1);
	return (s3);
}
