/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:55:16 by achu              #+#    #+#             */
/*   Updated: 2025/01/21 14:17:05 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ARG0 1

typedef struct s_pipex 
{
    int		infile_fd;
    int		outfile_fd;

	int		size_cmds;
    char    **path_cmds;
    char	***list_cmds;
}	t_pipex;

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"

void	ft_parse_args(t_pipex *data, int argc, char *argv[]);
void	ft_parse_env(t_pipex *data, char *envp[]);
void	ft_parse_path(t_pipex *data);
void	ft_parse_cmds(t_pipex *data, int argc, char *argv[]);
int	    ft_check_args(int argc, char *argv[]);
char 	*ft_check_cmd(t_pipex data, char *cmd);
int	    ft_exec(t_pipex *data);
void	ft_clean_up(t_pipex *data);

#endif