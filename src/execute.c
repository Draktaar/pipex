/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:33:58 by achu              #+#    #+#             */
/*   Updated: 2025/01/20 17:28:01 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_exec(t_pipex *data)
{
	int	i;
	int *fd[2];

	i = 0;
	(*fd)[2] = (int *)ft_calloc((*data).size_cmds + 1, sizeof(int[2]));
	if (!(*fd)[2])
		return (1);
	dup2((*data).infile_fd, STDIN_FILENO);
	while (i < (*data).size_cmds)
	{
		int		j;
		int		pid;
		char	*cmd;

		j = 0;
		cmd = ft_check_cmd(*data, data->list_cmds[i][0]);
		if (!cmd)
			return (1);
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			dup2(fd[i][1], STDIN_FILENO);
			if (i == (*data).size_cmds - 1)
				dup2(data->outfile_fd, STDOUT_FILENO);
			else
				dup2(fd[i - 1][0], STDOUT_FILENO);
			while (j < (*data).size_cmds)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			execve(cmd, (*data).list_cmds[i], NULL);
			error("Failed execute program");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
