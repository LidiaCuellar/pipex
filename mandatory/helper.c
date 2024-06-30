/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:36:56 by lcuellar          #+#    #+#             */
/*   Updated: 2024/04/05 16:30:30 by lcuellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (argc != 5)
		ft_error("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	pipex->parent_argv = argv;
	pipex->parent_env = env;
	get_path(pipex);
	if (pipe(pipex->tube) == -1)
		ft_error("Error in pipe creation.\n");
}

void	close_tube(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	get_path(t_pipex *pipex)
{
	char	**path;
	char	**env;

	env = pipex->parent_env;
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL){
		ft_putstr_fd("Error: PATH not found in environment.\n", 2);
		exit(-1);
	}
	*env += 5;
	path = ft_split(*env, ':');
	if (path == NULL){
		ft_putstr_fd("pipex: split function failed\n", 2);
		exit(-1);
	}
	pipex->path = path;
}
