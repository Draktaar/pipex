/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:47:20 by achu              #+#    #+#             */
/*   Updated: 2025/01/20 15:45:36 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/// @brief Search through every paths for the current commmand
/// @param data Struct for the path
/// @param cmd Search this command
/// @return The path + command if found, and Null if not found
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

int	ft_check_args(int argc, char *argv[])
{
	if (argc <= 3 + ARG0)
		error("Less than four arguments\n");

	if (access(argv[1], F_OK) < 0)
		return (error("Infile does not exist\n"), 0);	
	else if (access(argv[1], R_OK) < 0)
		return (error("Infile no read permission\n"), 0);
	else if (open(argv[1], O_RDONLY) < 0)
		return (error("Infile does not open\n"), 0);

	if (access(argv[argc - 1], W_OK) < 0)
		return (error("Outfile no write permission\n"), 0);
	else if (open(argv[argc - 1], O_WRONLY) < 0)
		return (error("Outfile does not open\n"), 0);

	return (1);
}