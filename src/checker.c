/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:47:20 by achu              #+#    #+#             */
/*   Updated: 2025/01/29 00:36:55 by achu             ###   ########.fr       */
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
		free(temp);
		i++;
	}
	return (NULL);
}

// Check if the outfile exist but cant be opened
// Check if there are missing args for the here_doc
// Check if there are missing args for the normal pipex
// Check if the infile exist and can be read for the normal pipex
int	ft_check_args(int argc, char *argv[])
{
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) < 0)
		return (error("Error: Outfile no write permission\n"), 0);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		if (argc < 5 + ARG0)
			return (error("Error: Need 5 arguments\n"), 0);
	}
	else
	{
		if (argc < 4 + ARG0)
			return (error("Error: Need 4 arguments\n"),0);
		if (access(argv[1], F_OK) < 0)
			return (error("Error: Infile does not exist\n"), 0);
		else if (access(argv[1], R_OK) < 0)
			return (error("Error: Infile no read permission\n"), 0);
	}
	return (1);
}
