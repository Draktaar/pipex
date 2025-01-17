/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:23:13 by achu              #+#    #+#             */
/*   Updated: 2025/01/17 18:31:10 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_cmds(char ***cmds)
{
	int i;
	int j;

	i = 0;
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
}
