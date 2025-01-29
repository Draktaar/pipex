/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:33:58 by achu              #+#    #+#             */
/*   Updated: 2025/01/29 01:37:11 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	wait_children(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->children[i])
	{
		if (data->children[i] != -1)
			waitpid(data->children[i], NULL, 0);
		i++;
	}
}

static pid_t	exe_child(t_pipex *data, int i)
{
	int		fd[2];
	pid_t	pid;
	char	***cmd;


	cmd = (*data).list_cmds;
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
		error("Error: Failed execute program");
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (pid);
}

static pid_t	exe_last(t_pipex *data, int i)
{
	pid_t	pid;
	char	***cmd;

	cmd = (*data).list_cmds;
	pid = fork();
	if (pid < 0)
		return (error("Error: Fork"), EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2(data->outfile_fd, STDOUT_FILENO);
		execve(cmd[i][0], cmd[i], NULL);
		error("Error: Failed execute program");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	ft_pipex(t_pipex *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < (*data).size_cmds)
	{
		if (access((*data).list_cmds[i][0], X_OK) < 0)
		{
			temp = ft_check_cmd(*data, data->list_cmds[i][0]);
			if (!temp)
				return (EXIT_FAILURE);
			free(data->list_cmds[i][0]);
			data->list_cmds[i][0] = temp;
		}
		if (i != (*data).size_cmds - 1)
			data->children[i] = exe_child(data, i);
		else
			data->children[i] = exe_last(data, i);
		i++;
	}
	data->children[i] = 0;
	wait_children(data);
	return (EXIT_SUCCESS);
}
