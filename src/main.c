/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:17:03 by phofer            #+#    #+#             */
/*   Updated: 2025/10/19 14:38:39 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command(char *arg, char **envp)
{
	char	**split_arg;
	char	*path;

	split_arg = ft_split(arg, ' ');
	if (!split_arg || !split_arg[0])
	{
		ft_putendl_fd("pipex: command not found", 2);
		if (split_arg)
			ft_free_tab(split_arg);
		exit (127);
	}
	path = get_path(split_arg[0], envp);
	execve(path, split_arg, envp);
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(split_arg[0], 2);
	if (path != split_arg[0])
		free(path);
	ft_free_tab(split_arg);
	exit(127);

}

void	child(char **argv, t_pipex pipex, char **envp)
{
	int	fd;

	fd = open_file(argv[1], 0);
	if (fd == -1)
		exit (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	command(argv[2], envp);
}

void	parent(char **argv, t_pipex pipex, char **envp)
{
	int	fd;

	fd = open_file(argv[4], STDOUT_FILENO);
	if (fd == -1)
		exit (1);
	dup2(fd, 1);
	close(fd);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	command(argv[3], envp);

}

int	close_wait(t_pipex pipex)
{
	int	status1;
	int	status2;
	int	exit_code;

	status1 = 0;
	status2 = 0;
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	waitpid(pipex.pid1, &status1, 0);
	waitpid(pipex.pid2, &status2, 0);
	if (WIFEXITED(status2))
	{
		exit_code = WEXITSTATUS(status2);
		return (exit_code);
	}
	if (WIFSIGNALED(status2))
		return (128 + WTERMSIG(status2));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		return (1);
	}
	if (pipe(pipex.pipefd) == -1)
		return (1);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (1);
	if (pipex.pid1 == 0)
		child(argv, pipex, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		return (1);
	if (pipex.pid2 == 0)
		parent(argv, pipex, envp);
	exit_status = close_wait(pipex);
	return (exit_status);
}
