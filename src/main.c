/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:09 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 14:27:22 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (argc < 4 + ARG0)
		return(error("Error: Less than four arguments\n"), EXIT_FAILURE);
	data.path_cmds = ft_parse_env(envp);
	if (!data.path_cmds)
		return (ft_clean_up(&data), EXIT_FAILURE);
	ft_parse_path(&data);
	ft_parse_cmds(&data, argc, argv);
	ft_parse_args(&data, argc, argv);
	if (!ft_check_fd(argc, argv))
		return (EXIT_FAILURE);
	ft_pipex(&data);
	ft_clean_up(&data);
	return (EXIT_SUCCESS);
}
