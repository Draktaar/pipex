/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:56:54 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 15:08:47 by achu             ###   ########.fr       */
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
	sub = (char **)malloc((ft_strdlen(env) + 1) * sizeof(char *));
	if (!sub)
		return (NULL);
	while (env[i])
	{
		if (i == 0)
		{
			sub[i] = ft_substr(env[0], 5, ft_strlen(env[0]));
			if (!sub)
				return (free(sub), NULL);
		}
		sub[i] = ft_strjoin(env[i], "/");
		if (!sub[i])
			return (free(sub), NULL);
		i++;
	}
	return (sub);
}

static char	**ft_parse_cmds(int argc, char *argv[])
{
	int		i;
	char	**cmds;

	i = 0;
	cmds = (char ***)ft_calloc((argc - 3) + 1, sizeof (char **));
	if (!cmds)
		return (NULL);
	while (i + 2 < argc - 1)
	{
		cmds[i] = ft_split(argv[i + 2], ' ');
		if (!cmds[i])
			return (clear_cmds(cmds), NULL);
		i++;
	}
	cmds[i] = 0;
	return (cmds);
}

int	ft_parse_args(t_pipex *data, int argc, char *argv[], char *envp[])
{
	char	**env;
	char	**path;

	env = ft_parse_env(envp);
	if (!env)
		return (0);
	data->path_cmds = ft_parse_paths(env);
	clear_path(env);
	if (!data->path_cmds)
		return (0);	
	data->list_cmds = ft_parse_cmds(argc, argv);
	if (!data->list_cmds)
		return (0);
	data->infile_fd = open(argv[1], O_RDONLY);
	data->outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (1);
}
