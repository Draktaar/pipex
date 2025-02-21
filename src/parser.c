/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:56:54 by achu              #+#    #+#             */
/*   Updated: 2025/02/21 18:06:36 by achu             ###   ########.fr       */
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
			path = ft_split(envp[i], ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	**ft_parse_paths(char **env)
{
	int		i;
	char	**sub;
	char	*temp;

	i = 0;
	sub = (char **)malloc((ft_strlen_dbl(env) + 1) * sizeof(char *));
	if (!sub)
		return (NULL);
	while (env[i])
	{
		sub[i] = ft_strjoin(env[i], "/");
		if (!sub[i])
			return (clear_double(sub), NULL);
		i++;
	}
	temp = ft_substr(sub[0], 5, ft_strlen(env[0]));
	if (!temp)
		return (clear_double(sub), NULL);
	free(sub[0]);
	sub[0] = temp;
	sub[i] = 0;
	return (sub);
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
	env = ft_parse_env(ep);
	if (!env)
		return (ft_clean_up(data), 0);
	data->path_cmds = ft_parse_paths(env);
	data->list_cmds = ft_parse_cmds(ac, av);
	clear_double(env);
	if (!data->path_cmds || !data->list_cmds)
		return (ft_clean_up(data), 0);
	data->size_cmds = ft_strlen_trpl((*data).list_cmds);
	return (1);
}
