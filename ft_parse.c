/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 08:29:45 by alimotta          #+#    #+#             */
/*   Updated: 2024/01/26 08:29:58 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** This f() is for the bonus part, it allows to read from standard input.
*/
void	ft_read_from_terminal(t_pipex *v, char **argv)
{
	int		buf_size;
	int		check;
	char	buffer[1024];

	check = 1;
	while (check != 0 && v->here_doc == 1)
	{
		write (1, "pipe heredoc> ", 14);
		buf_size = read(0, buffer, 1024);
		buffer[buf_size] = '\0';
		check = ft_strcmp(buffer, argv[2]);
		if (check != 0)
			write (v->in_fd, buffer, buf_size);
	}
	close (v->in_fd);
	v->in_fd = open("here_doc", O_RDWR | O_CREAT, 0666);
}

/*
** This f() copies the cmds when found.
** Each string contains the paths of the cmd that needs to be executed. 
*/
static int	ft_copy_cmds(t_pipex **v, int i, int j, int *check)
{
	while (++j < (*v)->lenght)
	{
		if (access((*v)->path[i][j], X_OK) == 0)
		{
			*check += 1;
			(*v)->len_s = ft_strlen((*v)->path[i][j]);
			(*v)->cmd[(*v)->i] = (char *)malloc((*v)->len_s + 1);
			if (!(*v)->cmd)
				return (-1);
			ft_strlcpy((*v)->cmd[(*v)->i], (*v)->path[i][j], (*v)->len_s + 1);
			break ;
		}
	}
	if (*check == (*v)->i)
	{
		if ((*v)->error == -1)
			(*v)->error = (*v)->i;
		(*v)->len_s = ft_strlen((*v)->arg[(*v)->i][0]);
		(*v)->cmd[(*v)->i] = (char *)malloc((*v)->len_s + 1);
		if (!(*v)->cmd)
			return (-1);
		ft_strlcpy((*v)->cmd[(*v)->i], (*v)->arg[(*v)->i][0], (*v)->len_s + 1);
		*check += 1;
	}
	return (0);
}

/*
** This f() create the cmd array.
** Each string contains the paths of the cmd that needs to be executed. 
*/
int	ft_parse_cmds(int argc, t_pipex *v)
{
	int	i;
	int	j;
	int	check;

	v->i = 0;
	i = 1;
	check = 0;
	v->error = -1;
	v->cmd = (char **)malloc(sizeof(char *) * (argc - 2));
	if (!v->cmd)
		return (-1);
	while (v->path[i] != 0)
	{
		j = -1;
		ft_copy_cmds(&v, i, j, &check);
		i++;
		v->i++;
	}
	v->cmd[v->i] = 0;
	if (v->error != -1)
		ft_error(v->cmd[v->error], 0);
	return (0);
}

/*
**This f() allocate memory for the pipes.
*/
static void	ft_allocate_pipe_memory(t_pipex **v)
{
	int	i;

	i = 0;
	(*v)->pipes = (int **)malloc((*v)->i * sizeof(int *));
	if (!(*v)->pipes)
		return ;
	while (i < (*v)->i)
	{
		(*v)->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!(*v)->pipes[i])
			return ;
		if (pipe((*v)->pipes[i]) == -1)
			ft_pipe_error();
		i++;
	}
}

/*
**This f() create the arg 2d array.
**Each array of args will be passed to execve() to execute the command.
*/
void	ft_parse_args(int argc, char **argv, t_pipex *v)
{
	int	i;

	v->arg = (char ***)malloc(sizeof(char **) * (argc - 2));
	if (!v->arg)
		return ;
	i = 2;
	if (v->here_doc == 1)
		i++;
	v->i = 0;
	while (i < argc - 1)
	{
		v->arg[v->i] = ft_split(argv[i], 32);
		i++;
		v->i++;
	}
	v->arg[v->i] = 0;
	ft_allocate_pipe_memory(&v);
}
