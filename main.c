/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:09 by achu              #+#    #+#             */
/*   Updated: 2025/01/14 18:48:19 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_parse_cmds(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < argc)
	{
		
	}
}

int	ft_parse_args()
{
	
}

int	ft_check_args(int argc, char *argv[])
{
	if (argc <= 3 + ARG0)
		ft_putstr_fd("Less than four arguments", 2);

	if (access(argv[0], R_OK) == -1)
		return (ft_putstr_fd("Infile no read permission", 2), 0);
	else if (open(argv[0], O_RDONLY) < 0)
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

	(void) argv;

	return 0;
}
