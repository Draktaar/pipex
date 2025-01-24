/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:33:58 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 14:06:27 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "pipex.h"

static int	exe_child(char ***cmd, int i)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) < 0)
		return (error("Error: Pipe"), EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (error("Error: Fork"), EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(cmd[i][0], cmd[i], NULL);
		error("Failed execute program");
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (EXIT_SUCCESS);
}

static int	exe_last(t_pipex *data, int i)
{
	int		pid;
	char	***cmd;

	cmd = (*data).list_cmds;
	pid = fork();
	if (pid < 0)
		return (error("Error: Fork"), EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2(data->outfile_fd, STDOUT_FILENO);
		execve(cmd[i][0], cmd[i], NULL);
		error("Failed execute program");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_pipex(t_pipex *data)
{
	int		i;
	char	*temp;

	i = 0;
	dup2((*data).infile_fd, STDIN_FILENO);
	while (i < (*data).size_cmds)
	{
		if (access((*data).list_cmds[i][0], X_OK) < 0)
		{
			temp = ft_check_cmd(*data, data->list_cmds[i][0]);
			if (!temp)
				return (error("Command not found"), EXIT_FAILURE);
			free(data->list_cmds[i][0]);
			data->list_cmds[i][0] = temp;
		}
		if (i != (*data).size_cmds - 1)
			exe_child(data->list_cmds, i);
		else
			exe_last(data, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
