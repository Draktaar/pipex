/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:09 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 18:36:38 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (ft_check_args(argc, argv))
		return (EXIT_FAILURE);
	if (!ft_strncmp("here_doc", argv[2], 8))
	{
		
	}
	else
	{
		if (!ft_parse_args(&data, argc, argv, envp))
			return (ft_clean_up(&data), EXIT_FAILURE);
		ft_pipex(&data);
	}
	ft_clean_up(&data);
	return (EXIT_SUCCESS);
}
