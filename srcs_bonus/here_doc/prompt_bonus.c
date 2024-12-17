/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:31:49 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 09:54:47 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static int	ft_recover_prompt(int fd_temp, char *lim, t_pipex *p)
{
	char	*line;

	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		(close(fd_temp), write(2, "get_next_line: error\n", 21), free(lim));
		(unlink(p->name_here_doc), free(p->name_here_doc));
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(lim, line) == 0)
	{
		free(line);
		return (1);
	}
	(write(fd_temp, line, ft_strlen(line)), free(line));
	return (0);
}

void	ft_prompt(char **av, t_pipex *p)
{
	int		fd_temp;
	char	*lim;

	create_here_doc(p);
	fd_temp = open(p->name_here_doc, O_CREAT | O_APPEND | O_WRONLY, 0744);
	if (fd_temp == -1)
		(perror(p->name_here_doc), free(p->name_here_doc), exit(EXIT_FAILURE));
	lim = ft_strjoin(av[2], "\n");
	if (!lim)
	{
		(close(fd_temp), write(2, "ft_strjoin: error\n", 18));
		(unlink(p->name_here_doc), free(p->name_here_doc));
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (ft_recover_prompt(fd_temp, lim, p) == 1)
			break ;
	}
	p->prompt = 1;
	(close(fd_temp), free(lim));
}
