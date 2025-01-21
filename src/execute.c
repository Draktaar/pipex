/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:33:58 by achu              #+#    #+#             */
/*   Updated: 2025/01/21 18:27:38 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int    ft_child(t_pipex *data, int index)
{
    int		fd[2];
    int		pid;
    char	*cmd;

    cmd = ft_check_cmd(*data, data->list_cmds[index][0]);
    if (!cmd)
        return (EXIT_FAILURE);
    if (pipe(fd) < 0)
        return (EXIT_FAILURE);
	pid = fork();
    if (pid < 0)
        return (EXIT_FAILURE);
    else if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(cmd, (*data).list_cmds[index], NULL);
        error("Failed execute program");
        exit(EXIT_FAILURE);
    }
	else
	{
    	close(fd[1]);
    	dup2(fd[0], STDIN_FILENO);
    	close(fd[0]);
	}
    return (EXIT_SUCCESS);
}

int    ft_exec(t_pipex *data)
{
    int    i;

    i = 0;
	dup2((*data).infile_fd, STDIN_FILENO);
    while (i < (*data).size_cmds)
    {
        ft_child(data, i);
        i++;
    }
    return (EXIT_SUCCESS);
}
