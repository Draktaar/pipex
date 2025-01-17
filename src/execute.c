/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:33:58 by achu              #+#    #+#             */
/*   Updated: 2025/01/17 18:31:38 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_exec(t_pipex *data)
{
	int pipefd[2];
	int	pid1;
	int	pid2;

	dup2((*data).infile_fd, STDIN_FILENO);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDIN_FILENO);
		close(pipefd[1]);
		execve((*data).list_cmds[0][0], (*data).list_cmds[0], NULL);
	}

	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDOUT_FILENO);
		close(pipefd[0]);
		execve((*data).list_cmds[1][0], (*data).list_cmds[1], NULL);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
