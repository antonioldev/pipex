/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_folder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:46:06 by alimotta          #+#    #+#             */
/*   Updated: 2024/02/01 10:46:08 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2 [i]);
		i++;
	}
	return (0);
}

static int	ft_number_of_folders(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	return (i);
}

static int	find_path(char **envp, int *j)
{
	int	i;

	i = 0;
	*j = 0;
	while (envp[i] && *j == 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

/*
**This f() find all paths where commands can be found.
*/
void	ft_parse_cmds_folder(int argc, char **argv, char **envp, t_pipex *v)
{
	int	i;
	int	j;
	int	y;

	i = find_path(envp, &j);
	v->path = (char ***)malloc(sizeof(char **) * argc);
	if (!v->path)
		return ;
	v->path[j++] = ft_split(envp[i] + 5, 58);
	v->lenght = ft_number_of_folders(v->path[0]);
	y = 1;
	if (v->here_doc == 1)
		y++;
	while (++y < argc - 1)
	{
		v->path[j] = (char **)malloc(sizeof(char *) * v->lenght);
		if (!v->path[j])
			return ;
		i = -1;
		while (++i < v->lenght)
			v->path[j][i] = ft_strjoin(v->path[0][i], argv[y]);
		j++;
	}
	v->path[j] = 0;
}
