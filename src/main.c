/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:09 by achu              #+#    #+#             */
/*   Updated: 2025/01/20 15:46:13 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (!ft_check_args(argc, argv))
		return (ft_clean_up(&data), EXIT_FAILURE);
	ft_parse_env(&data, envp);
	ft_parse_path(&data);
	ft_parse_cmds(&data, argc, argv);
	ft_parse_args(&data, argc, argv);
	ft_exec(&data);
	ft_clean_up(&data);
	return (EXIT_SUCCESS);
}
