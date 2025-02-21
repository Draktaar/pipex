/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:33:59 by achu              #+#    #+#             */
/*   Updated: 2025/02/21 18:05:51 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_limit(char *limit, int fd)
{
	size_t	len;
	char	*line;

	len = ft_strlen(limit);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limit, line, len) == 0 && \
		(line[len] == '\0' || line[len] == '\n'))
		{
			free(line);
			get_next_line(-1);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	ft_heredoc(t_pipex *data, char *limit)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return (error("Error: Pipe"), EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (error("Error: Fork"), EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd[0]);
		ft_limit(limit, fd[1]);
		close(fd[1]);
		ft_clean_up(data);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}
