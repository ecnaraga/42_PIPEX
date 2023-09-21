/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:47:17 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 09:56:29 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_free_fd_p(int **fd_p, int j)
{
	if (j != -1)
	{
		while (--j >= 0)
			free(fd_p[j]);
		free(fd_p);
	}
	else
	{
		while (fd_p[++j])
			free(fd_p[j]);
		free(fd_p);
	}
}

void	ft_exit(t_pipex *p, int fd_1, int fd_2, int j)
{
	if (fd_1 > -1)
		close(fd_1);
	if (fd_2 > -1)
		close(fd_2);
	if (p->good_path)
		free(p->good_path);
	if (p->path)
		ft_free_split(p->path);
	if (p->cmd_opt)
		ft_free_split(p->cmd_opt);
	if (p->fd_p)
		ft_free_fd_p(p->fd_p, j);
	if (p->name_here_doc)
		free(p->name_here_doc);
	exit(EXIT_FAILURE);
}

void	ft_perr(int err, char *cmd)
{
	char	*str;

	if (err == E_NO_CMD)
	{
		if (ck_char(cmd, '/') > 0)
		{
			str = ft_strjoin("bash: ", cmd);
			perror(str);
		}
		else
		{
			str = ft_strjoin(cmd, ": command not found\n");
			write(2, str, ft_strlen(str));
		}
		free(str);
	}
	else if (err == E_STRJOIN)
		write(2, "ft_strjoin: error malloc\n", 26);
	else if (err == E_STRDUP)
		write(2, "ft_strdup: error malloc\n", 25);
}
