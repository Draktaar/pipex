/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:56:54 by achu              #+#    #+#             */
/*   Updated: 2025/01/24 14:30:55 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parse_args(t_pipex *data, int argc, char *argv[])
{
	data->infile_fd = open(argv[1], O_RDONLY);
	data->outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

char	**ft_parse_env(char *envp[])
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
		else
			return (NULL);
		i++;
	}
	return (NULL);
}

char	*ft_parse_path(t_pipex *data)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen((*data).path_cmds[0]);
	while ((*data).path_cmds[i])
	{
		if (i == 0)
		{
			temp = ft_substr((*data).path_cmds[0], 5, len);
			if (!temp)
				return ;
			free(data->path_cmds[0]);
			data->path_cmds[0] = temp;
		}
		temp = ft_strjoin((*data).path_cmds[i], "/");
		free(data->path_cmds[i]);
		data->path_cmds[i] = temp;
		i++;
	}
}

void	ft_parse_cmds(t_pipex *data, int argc, char *argv[])
{
	int	i;

	i = 0;
	data->list_cmds = (char ***)calloc(argc - 2, sizeof (char **));
	if (!data->list_cmds)
		return (exit(EXIT_FAILURE));
	while (i + 2 < argc - 1)
	{
		data->list_cmds[i] = ft_split(argv[i + 2], ' ');
		if (!data->list_cmds[i])
			return (exit(EXIT_FAILURE));
		i++;
	}
	data->list_cmds[i] = 0;
	data->size_cmds = i;
}
