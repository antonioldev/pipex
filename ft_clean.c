/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 07:32:12 by alimotta          #+#    #+#             */
/*   Updated: 2024/01/26 07:32:26 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_clean_path(t_pipex **v)
{
	int	i;
	int	j;

	i = 0;
	while ((*v)->path[i] != 0)
	{
		j = 0;
		while (j < (*v)->lenght)
		{
			free((*v)->path[i][j]);
			j++;
		}
		free((*v)->path[i]);
		i++;
	}
	free((*v)->path);
}

/*
**This f() free the memory allocated with malloc and close fd for file1 & file2
*/
void	ft_clean(t_pipex *v, int i, int j)
{
	ft_clean_path(&v);
	i = 0;
	while (v->arg[i] != 0)
	{
		j = 0;
		while (v->arg[i][j] != 0)
		{
			free(v->arg[i][j]);
			j++;
		}
		free(v->pipes[i]);
		free(v->arg[i]);
		free(v->cmd[i]);
		i++;
	}
	free(v->pipes);
	free(v->cmd);
	free(v->arg);
	close(v->in_fd);
	close(v->out_fd);
	if (v->here_doc == 1 || v->here_doc == 2)
		unlink("here_doc");
}

int	ft_error(char *str, int i)
{
	if (i == 0)
	{
		errno = 2;
		write(1, str, ft_strlen(str));
		return (perror(" : Command not found!"), errno);
	}
	else
	{
		errno = 13;
		write(1, str, ft_strlen(str));
		return (perror(" "), errno);
	}
}

void	ft_close_fd(int fd)
{
	close(fd);
	exit(EXIT_FAILURE);
}

void	ft_close_two_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
	exit(EXIT_FAILURE);
}
