/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:56:54 by achu              #+#    #+#             */
/*   Updated: 2025/03/09 17:50:16 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_parse_env(char *envp[])
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	***ft_parse_cmds(int argc, char *argv[])
{
	int		i;
	int		step;
	char	***cmds;

	i = 0;
	step = 2;
	if (is_heredoc(argv[1]))
		step += 1;
	cmds = (char ***)ft_calloc((argc - step), sizeof(char **));
	if (!cmds)
		return (NULL);
	while (step + i < argc - 1)
	{
		cmds[i] = ft_split(argv[step + i], ' ');
		if (!cmds[i])
			return (clear_triple(cmds), NULL);
		i++;
	}
	cmds[i] = 0;
	return (cmds);
}

static pid_t	*ft_parse_pid(int argc, char *argv[])
{
	int		i;
	int		step;
	pid_t	*children;

	i = 0;
	step = 2;
	if (is_heredoc(argv[1]))
		step += 1;
	children = (pid_t *)ft_calloc((argc - step), sizeof(pid_t));
	if (!children)
		return (NULL);
	return (children);
}

int	ft_parse_args(t_pipex *data, int ac, char *av[], char *ep[])
{
	char	**env;

	data->av = av;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->children = ft_parse_pid(ac, av);
	if (!data->children)
		return (0);
	data->env = ft_parse_env(ep);
	data->list_cmds = ft_parse_cmds(ac, av);
	if (!data->list_cmds)
		return (ft_clean_up(data), 0);
	data->size_cmds = ft_strlen_trpl((*data).list_cmds);
	return (1);
}
