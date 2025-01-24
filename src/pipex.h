/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:55:16 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 18:03:30 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"

# define ARG0 1

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;

	int		size_cmds;
	char	**path_cmds;
	char	***list_cmds;
}	t_pipex;

int		ft_parse_args(t_pipex *data, int argc, char *argv[], char *envp[]);
int		ft_check_args(int argc, char *argv[]);
char	*ft_check_cmd(t_pipex data, char *cmd);
int		ft_pipex(t_pipex *data);
void	ft_clean_up(t_pipex *data);
void	clear_path(char **paths);
void	clear_cmds(char ***cmds);

#endif