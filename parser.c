/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:56:54 by achu              #+#    #+#             */
/*   Updated: 2025/01/15 10:49:24 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void cmd_clear(char ***cmds)
{
	int	c;

	c = 0;
	while (cmds[c])
    {
		free(cmds[c]);
        c++;
    }
    free(cmds);
}

int cmd_size(char ***cmds)
{
	int i;

	i = 0;
	while (cmds[i])
		i++;
	return (0);
}

char	***ft_parse_cmds(int argc, char *argv[])
{
    int		i;
    char    ***cmds;

    i = 0;
    cmds = (char ***)calloc(argc - 2, sizeof (char **));
    if (!cmds)
        return (0);
    while (i + 2 < argc - 1)
    {
        cmds[i] = ft_split(argv[i + 2], ' ');
        if (!cmds[i])
            return (cmd_clear(cmds), 0);
        i++;
    }
    cmds[i] = 0;
    return (cmds);
}

void	ft_parse_(t_pipex *data, int argc, char *argv[])
{
	data->infile_fd = open(argv[1], O_RDONLY);
    data->outfile_fd = open(argv[argc], O_WRONLY);
}
