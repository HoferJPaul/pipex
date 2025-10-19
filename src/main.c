/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:17:03 by phofer            #+#    #+#             */
/*   Updated: 2025/10/19 12:47:16 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, t_pipex pipex, char **envp)
{
	int	fd;

	fd = open_file(argv[1], 0);
	dup2(fd, 0);
	close(fd);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	command(argv[2], envp);
}

void	parent(char **argv, t_pipex pipex, char **envp)
{
	int	fd;

	fd = open_file(argv[4], 1);
	dup2(fd, 1);
	close(fd);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	command(argv[3], envp);

}

void	check_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit (1);
	}
}

void	close_wait(t_pipex pipex)
{
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	check_argc(argc);
	if (pipe(pipex.pipefd) == -1)
		exit (1);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		exit(1);
	if (pipex.pid1 == 0)
		child(argv, pipex, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		exit(1);
	if (pipex.pid2 == 0)
		parent(argv, pipex, envp);
	close_wait(pipex);
	return (0);
}
