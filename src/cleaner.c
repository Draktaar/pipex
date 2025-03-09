/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:23:13 by achu              #+#    #+#             */
/*   Updated: 2025/03/09 17:47:56 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_double(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	clear_triple(char ***ptr)
{
	int	i;
	int	j;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		j = 0;
		while (ptr[i][j])
		{
			free(ptr[i][j]);
			j++;
		}
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	ft_clear_fd(t_pipex *data)
{
	if ((*data).infile_fd != -1)
		close (data->infile_fd);
	if ((*data).outfile_fd != -1)
		close (data->outfile_fd);
}

void	ft_clean_up(t_pipex *data)
{
	if (data->children)
		free(data->children);
	clear_double(data->env);
	clear_triple(data->list_cmds);
	ft_clear_fd(data);
}
