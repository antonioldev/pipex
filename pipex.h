/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:01:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/01/25 13:01:48 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# define BUFFER_SIZE 1000

typedef struct s_pipex
{
	int		i;
	int		len_s;
	int		in_fd;
	int		out_fd;
	int		here_doc;
	int		lenght;
	int		error;
	int		**pipes;
	int		prev_pipe;
	pid_t	pids;
	char	**cmd;
	char	***path;
	char	***arg;
}				t_pipex;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_parse_cmds(int argc, t_pipex *v);
int		ft_error(char *str, int i);
void	ft_read_from_terminal(t_pipex *v, char **argv);
void	ft_clean(t_pipex *v, int i, int j);
void	ft_parse_cmds_folder(int argc, char **argv, char **envp, t_pipex *v);
void	ft_parse_args(int argc, char **argv, t_pipex *v);
void	ft_exec_first(t_pipex *v, int i);
void	ft_exec_last(t_pipex *v, int i, int argc, char **argv);
void	ft_close_fd(int fd);
void	ft_close_two_fd(int fd1, int fd2);
void	ft_pipe_error(void);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

#endif
