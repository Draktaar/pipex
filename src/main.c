/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:09 by achu              #+#    #+#             */
/*   Updated: 2025/01/29 00:07:51 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;
	if (!ft_check_args(argc, argv))
		return (1);
	if (!ft_parse_args(&data, argc, argv, envp))
		return (1);
	if (ft_strncmp("here_doc", argv[2], 8) == 0)
	{
		data.infile_fd = -1;
		data.outfile_fd = open (argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (data.outfile_fd < 0)
			return (ft_clear_fd(&data), 1);
	}
	else
	{
		data.infile_fd = open(argv[1], O_RDONLY);
		data.outfile_fd = open (argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (data.infile_fd < 0 || data.outfile_fd < 0)
			return (ft_clear_fd(&data), 1);
		ft_pipex(&data);
	}
	ft_clean_up(&data);
	return (0);
}
