/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:55:16 by achu              #+#    #+#             */
/*   Updated: 2025/02/21 18:32:36 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../lib/libft/libft.h"

# define ARG0 1

typedef struct s_pipex
{
	char	**av;
	pid_t	*children;
	int		infile_fd;
	int		outfile_fd;

	int		size_cmds;
	char	**path_cmds;
	char	***list_cmds;
}	t_pipex;

int		ft_parse_args(t_pipex *data, int ac, char *av[], char *ep[]);
int		ft_check_args(int argc, char *argv[]);
char	*ft_check_cmd(char **path, char *cmd);
int		ft_pipex(t_pipex *data);
int		ft_heredoc(t_pipex *data, char *limit);
void	ft_clean_up(t_pipex *data);
void	ft_clear_fd(t_pipex *data);
void	clear_double(char **paths);
void	clear_triple(char ***cmds);
void	ft_dupin(int fd[2]);
void	ft_dupout(int fd[2]);
int		is_heredoc(char *arg);

#endif