/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:09 by achu              #+#    #+#             */
/*   Updated: 2025/02/21 18:17:27 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *ev[])
{
	t_pipex	data;

	if (ft_check_args(ac, av) == 0)
		return (1);
	if (ft_parse_args(&data, ac, av, ev) == 0)
		return (1);
	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		data.infile_fd = 0;
		data.outfile_fd = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (ft_heredoc(&data, av[2]) < 0)
			return (ft_clear_fd(&data), 1);
	}
	else
	{
		data.infile_fd = open(av[1], O_RDONLY);
		data.outfile_fd = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(data.infile_fd, STDIN_FILENO);
	}
	return (ft_pipex(&data));
}
