/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:48:34 by lcuellar          #+#    #+#             */
/*   Updated: 2024/04/05 16:31:24 by lcuellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_pipex
{
	int		tube[2];
	pid_t	first_child;
	pid_t	second_child;
	char	**parent_argv;
	char	**parent_env;
	char	**argv_childs;
	char	**path;
}			t_pipex;

void		initialize(t_pipex *pipex, int argc, char **argv, char **env);
void		open_tube(t_pipex *pipex);
void		close_tube(t_pipex *pipex);
void		get_path(t_pipex *pipex);
void		ft_error(char *str);

#endif