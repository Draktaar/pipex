/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:47:20 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 13:51:40 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Search through every paths for the current commmand
// and return the path with the command if found, or Null if not
char	*ft_check_cmd(t_pipex data, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (data.path_cmds[i])
	{
		temp = ft_strjoin(data.path_cmds[i], cmd);
		if (!temp)
			return (NULL);
		if (access(temp, X_OK) == 0)
			return (temp);
		i++;
	}
	free(temp);
	return (NULL);
}

int	ft_check_fd(int argc, char *argv[])
{
	if (access(argv[1], F_OK) < 0)
		return (error("Error: Infile does not exist\n"), 0);
	else if (access(argv[1], R_OK) < 0)
		return (error("Error: Infile no read permission\n"), 0);
	else if (open(argv[1], O_RDONLY) < 0)
		return (error("Error: Infile does not open\n"), 0);

	if (open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644) < 0)
		return (error("Error: Outfile does not open\n"), 0);
	else if (access(argv[argc - 1], W_OK) < 0)
		return (error("Error: Outfile no write permission\n"), 0);
	return (1);
}
