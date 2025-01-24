/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:23:13 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 14:28:07 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_path(char **paths)
{
	int	i;

	i = 0;
	if (!paths || !*paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	clear_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	if (!cmds || !*cmds || !**cmds)
		return ;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	ft_clean_up(t_pipex *data)
{
	clear_cmds(data->list_cmds);
	clear_path(data->path_cmds);
	close(data->infile_fd);
	close(data->outfile_fd);
}
