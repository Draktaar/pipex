/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:33:58 by achu              #+#    #+#             */
/*   Updated: 2025/03/09 17:48:38 by achu             ###   ########.fr       */
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
	pid_t	pid;
	int		fd[2];
	char	*temp;
	char	***cmd;

	cmd = (*data).list_cmds;
	if (pipe(fd) < 0)
		return (error("Error: Pipe"), EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (error("Error: Fork"), EXIT_FAILURE);
	else if (pid == 0)
	{
		ft_dupout(fd);
		if (data->infile_fd < 0 && i == 0)
			(ft_clean_up(data), exit(126));
		temp = ft_check_cmd(data->env, cmd[i][0]);
		if (!temp)
			(error("Error: Command not found"), ft_clean_up(data), exit(127));
		execve(temp, cmd[i], NULL);
		(error("Error: Failed execute program"), ft_clean_up(data), \
		free(temp), exit(126));
	}
	ft_dupin(fd);
	return (pid);
}

static pid_t	exe_last(t_pipex *data, int i)
{
	pid_t	pid;
	char	*temp;
	char	***cmd;

	cmd = (*data).list_cmds;
	pid = fork();
	if (pid < 0)
		return (error("Error: Fork"), EXIT_FAILURE);
	else if (pid == 0)
	{
		if (data->outfile_fd < 0)
			(ft_clean_up(data), exit(126));
		temp = ft_check_cmd(data->env, cmd[i][0]);
		if (!temp)
			(error("Error: Command not found"), ft_clean_up(data), exit(127));
		dup2(data->outfile_fd, STDOUT_FILENO);
		execve(temp, cmd[i], NULL);
		error("Error: Failed execute program");
		ft_clean_up(data);
		free(temp);
		exit(126);
	}
	return (pid);
}

int	ft_pipex(t_pipex *data)
{
	int		i;

	i = 0;
	while (data->list_cmds[i])
	{
		if (i == (*data).size_cmds - 1)
			data->children[i] = exe_last(data, i);
		else
			data->children[i] = exe_child(data, i);
		i++;
	}
	data->children[i] = 0;
	wait_children(data);
	ft_clean_up(data);
	return (EXIT_SUCCESS);
}
