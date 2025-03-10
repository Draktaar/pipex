/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:47:20 by achu              #+#    #+#             */
/*   Updated: 2025/03/10 01:06:15 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Search through every paths for the current commmand
// and return the path with the command if found, or Null if not
char	*ft_check_cmd(char **envp, char *cmd)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (envp && envp[i])
	{
		temp = ft_strjoin(envp[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
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
	if (argc < 4 + ARG0)
		return (error("Error: Need 4 arguments"), 0);
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) < 0)
		error("Error: Outfile no write permission");
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		if (argc < 5 + ARG0)
			return (error("Error: Need 5 arguments"), 0);
	}
	else
	{
		if (access(argv[1], F_OK) < 0)
			error("Error: Infile does not exist");
		else if (access(argv[1], R_OK) < 0)
			error("Error: Infile no read permission");
	}
	return (1);
}
