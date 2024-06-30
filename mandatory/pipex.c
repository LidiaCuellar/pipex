/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:48:36 by lcuellar          #+#    #+#             */
/*   Updated: 2024/04/05 20:25:24 by lcuellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

static	void	first_child(t_pipex *pipex, char *command);
static	void	second_child(t_pipex *pipex, char *command);
static	void	execute(t_pipex *pipex, char *command);
static	char	*find_executable(t_pipex *pipex);

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		exit_status;
	int		exit_status2;

	initialize(&pipex, argc, argv, env);
	first_child(&pipex, argv[2]);
	second_child(&pipex, argv[3]);
	close_tube(&pipex);
	waitpid(pipex.first_child, &exit_status, 0);
	waitpid(pipex.second_child, &exit_status2, 0);
	ft_free_split(pipex.path);
	exit(exit_status2);
}

static	void	first_child(t_pipex *pipex, char *command)
{
	int	infile;

	pipex->first_child = fork();
	if (pipex->first_child == 0)
	{
		close(pipex->tube[0]);
		infile = open(pipex->parent_argv[1], O_RDONLY);
		if (infile == -1)
		{
			close(pipex->tube[1]);
			ft_free_split(pipex->path);
			ft_putstr_fd("Error in opening input file.\n", 2);
			exit(-1);
		}
		dup2(pipex->tube[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		close(pipex->tube[1]);
		close(infile);
		execute(pipex, command);
	}
}

static	void	second_child(t_pipex *pipex, char *command)
{
	int	outfile;

	pipex->second_child = fork();
	if (pipex->second_child == 0)
	{
		close(pipex->tube[1]);
		outfile = open(pipex->parent_argv[4], O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (outfile == -1)
		{
			close(pipex->tube[0]);
			ft_free_split(pipex->path);
			ft_putstr_fd("Error in creating output file.\n", 2);
			perror(pipex->parent_argv[4]);
			exit(-1);
		}
		dup2(pipex->tube[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(pipex->tube[0]);
		close(outfile);
		execute(pipex, command);
	}
}

static	void	execute(t_pipex *pipex, char *command)
{
	char	*executable;

	pipex->argv_childs = ft_split(command, ' ');
	if (!pipex->argv_childs)
	{
		ft_putstr_fd("Split function failed\n", 2);
		exit(-1);
	}
	executable = find_executable(pipex);
	if (!executable)
	{
		ft_putstr_fd(pipex->argv_childs[0], 2);
		ft_putstr_fd(": Command not found.\n", 2);
		ft_free_split(pipex->argv_childs);
		ft_free_split(pipex->path);
		exit(127);
	}
	execve(executable, pipex->argv_childs, pipex->parent_env);
}

static	char	*find_executable(t_pipex *pipex)
{
	char	*executable;
	char	*command;
	char	*tmp;
	int		i;

	command = pipex->argv_childs[0];
	if (access(command, X_OK) == 0)
	{
		return (command);
	}
	i = 0;
	while (pipex->path[i])
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		executable = ft_strjoin(tmp, command);
		free(tmp);
		if (access(executable, X_OK) == 0)
		{
			return (executable);
		}
		free(executable);
		i++;
	}
	return (NULL);
}
