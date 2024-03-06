/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 07:40:25 by alimotta          #+#    #+#             */
/*   Updated: 2024/01/26 07:40:27 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == '\n' && s2[i] == '\0')
			return (0);
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2 [i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen((char *)src);
	if (src_len + 1 < size)
	{
		while (i < src_len + 1)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else if (size != 0)
	{
		while (i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[size - 1] = '\0';
	}
	return (src_len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*p_dest;
	unsigned const char	*p_src;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	i = 0;
	p_dest = dest;
	p_src = src;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;

	if ((!dest || !src) && !size)
		return (0);
	src_len = ft_strlen((char *)src);
	dest_len = ft_strlen((char *)dest);
	if (dest_len >= size)
		dest_len = size;
	if (size <= dest_len)
		return (dest_len + src_len);
	if (src_len < size - dest_len)
		ft_memcpy(dest + dest_len, (char *)src, src_len + 1);
	else
		ft_memcpy(dest + dest_len, (char *)src, size - dest_len - 1);
	dest[size - 1] = '\0';
	return (dest_len + src_len);
}
