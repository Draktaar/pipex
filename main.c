/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:09 by achu              #+#    #+#             */
/*   Updated: 2025/01/14 22:06:54 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_args(int argc, char *argv[])
{
	if (argc < 4 + ARG0)
		ft_putstr_fd("Less than four arguments", 2);

	if (access(argv[1], R_OK) == -1)
		return (ft_putstr_fd("Infile no read permission", 2), 0);
	else if (open(argv[1], O_RDONLY) < 0)
		return (ft_putstr_fd("Infile does not open", 2), 0);

	if (access(argv[argc], W_OK) == -1)
		return (ft_putstr_fd("Outfile no write permission", 2), 0);
	else if (open(argv[argc], O_WRONLY) < 0)
		return (ft_putstr_fd("Outfile does not open", 2), 0);
	
	return (0);
}

int	main(int argc, char *argv[])
{
	t_pipex	data;

	ft_parse_cmds(&data, argc, argv);
	
	return 0;
}
