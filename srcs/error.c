/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:47:17 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 09:56:14 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_exit(t_pipex *p, int fd_1, int fd_2)
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
