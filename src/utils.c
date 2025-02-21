/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:24:44 by achu              #+#    #+#             */
/*   Updated: 2025/02/21 18:33:04 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dupin(int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_dupout(int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

int	is_heredoc(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (ft_strncmp(arg, "here_doc", len) == 0 && \
		(arg[len] == '\0' || arg[len] == '\n'))
		return (1);
	return (0);
}
