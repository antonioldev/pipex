/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:48:26 by alimotta          #+#    #+#             */
/*   Updated: 2024/01/26 12:48:28 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_fork_error(void)
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

void	ft_pipe_error(void)
{
	perror("Pipe creation failed");
	exit(EXIT_FAILURE);
}

/*
**This f() is called for all the cmds except for the last one.
*/
void	ft_exec_first(t_pipex *v, int i)
{
	v->pids = fork();
	if (v->pids == -1)
		ft_fork_error();
	if (v->pids == 0)
	{
		close (v->pipes[i][0]);
		dup2(v->pipes[i][1], STDOUT_FILENO);
		if (i > 0)
			dup2(v->prev_pipe, STDIN_FILENO);
		else
			dup2(v->in_fd, STDIN_FILENO);
		execve(v->cmd[i], v->arg[i], NULL);
		ft_clean(v, 0, 0);
		exit(EXIT_FAILURE);
	}
	else
	{
		close (v->pipes[i][1]);
		v->prev_pipe = v->pipes[i][0];
		waitpid(v->pids, NULL, 0);
	}
}

/*
**This f() is called for the last cmd to redirect the output to file2.
*/
void	ft_exec_last(t_pipex *v, int i, int argc, char **argv)
{
	v->pids = fork();
	if (v->pids == -1)
		ft_fork_error();
	if (v->pids == 0)
	{
		close (v->pipes[i][0]);
		dup2(v->prev_pipe, STDIN_FILENO);
		if (access(argv[argc - 1], W_OK) == 0)
		{
			dup2(v->out_fd, STDOUT_FILENO);
			execve(v->cmd[i], v->arg[i], NULL);
			ft_clean(v, 0, 0);
			exit(EXIT_FAILURE);
		}
		dup2(STDOUT_FILENO, STDERR_FILENO);
		ft_error(argv[argc - 1], 1);
	}
	else
	{
		close (v->pipes[i][1]);
		waitpid(v->pids, NULL, 0);
		close (v->prev_pipe);
	}
}
