/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:55:16 by achu              #+#    #+#             */
/*   Updated: 2025/01/14 18:51:06 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ARG0 1

typedef struct s_pipex 
{
    int		infile_fd;
    int		outfile_fd;

	int		cmd_len;
    char	***cmd_list;
}	t_pipex;

# include <fcntl.h>
# include <unistd.h>
# include "lib/libft/libft.h"
# include "lib/printf/ft_printf.h"

#endif