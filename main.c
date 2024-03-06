/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:36:56 by alimotta          #+#    #+#             */
/*   Updated: 2024/02/07 10:36:59 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_print_error(int i)
{
	errno = i;
	if (i == 1)
		perror("Not Enough arguments");
	else if (i == 2)
		perror("");
	return (errno);
}

void	ft_read_from_random(int argc, char **argv, t_pipex **v)
{
	int		fd_path;
	ssize_t	bytes;
	char	buffer[BUFFER_SIZE];

	fd_path = open(argv[1], O_RDONLY);
	if (fd_path == -1)
		exit(EXIT_FAILURE);
	(*v)->in_fd = open("here_doc", O_RDWR | O_CREAT, 0666);
	if ((*v)->in_fd == -1)
		ft_close_fd(fd_path);
	bytes = read(fd_path, buffer, BUFFER_SIZE - 1);
	if (bytes == -1)
		ft_close_two_fd(fd_path, (*v)->in_fd);
	buffer[bytes] = '\0';
	bytes = write((*v)->in_fd, buffer, bytes);
	if (bytes == -1)
		ft_close_two_fd(fd_path, (*v)->in_fd);
	(*v)->here_doc = 2;
	close(fd_path);
	close((*v)->in_fd);
	(*v)->in_fd = open("here_doc", O_RDWR | O_CREAT, 0777);
	(*v)->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

/*
**This f() check if we pass the right number of arguments and if files exist.
**For file2, if the program can't open the file, it will create it.
*/
int	ft_check_args(int argc, char **argv, t_pipex *v)
{
	v->here_doc = 0;
	if (argc < 5)
		return (ft_print_error(1));
	else if (ft_strcmp((argv[1]), "/dev/urandom") == 0
		|| ft_strcmp((argv[1]), "/dev/random") == 0)
		ft_read_from_random(argc, argv, &v);
	else if (ft_strcmp((argv[1]), "here_doc") != 0)
	{
		v->in_fd = open(argv[1], O_RDONLY);
		if (v->in_fd == -1)
		{
			v->in_fd = open("here_doc", O_RDWR | O_CREAT, 0666);
			v->here_doc = 2;
		}
		v->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else
	{
		v->in_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
		v->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
		v->here_doc = 1;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	v;

	if (ft_check_args(argc, argv, &v) == 0)
	{
		ft_parse_args(argc, argv, &v);
		ft_parse_cmds_folder(argc, argv, envp, &v);
		ft_parse_cmds(argc, &v);
		if (v.here_doc == 1)
			ft_read_from_terminal(&v, argv);
		i = 0;
		while (i < v.i)
		{
			if (i < v.i - 1)
				ft_exec_first(&v, i);
			else
				ft_exec_last(&v, i, argc, argv);
			i++;
		}
		ft_clean(&v, 0, 0);
	}
	return (0);
}
