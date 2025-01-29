/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:33:59 by achu              #+#    #+#             */
/*   Updated: 2025/01/29 18:18:07 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_limit(t_pipex *data, int fd[2], char *limit)
{
	char	*stdin;
	size_t	len;

	close(fd[0]);
	len = ft_strlen(limit);
	stdin = get_next_line(STDIN_FILENO);
	while (stdin)
	{
		if (ft_strncmp(limit, stdin, len) == 0 && (stdin[len] == '\0' || stdin[len] == '\n'))
		{
			close(fd[1]);
			free(stdin);
			ft_clean_up(data);
			get_next_line(-1);
			exit(EXIT_FAILURE);
		}
		write(fd[1], stdin, ft_strlen(stdin));
		free(stdin);
		stdin = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
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
		ft_limit(data, fd, limit);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}