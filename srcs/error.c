/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:47:17 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 11:14:29 by garance          ###   ########.fr       */
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

static int	ft_check_cmd(char *cmd)
{
	int		i;
	size_t	count_slash;
	size_t	count_space;

	i = -1;
	count_slash = 0;
	count_space = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '/')
			count_slash++;
		if (cmd[i] == ' ')
			count_space++;
	}
	if (count_slash == ft_strlen(cmd))
		return (1);
	if (count_slash > 0 && count_slash + count_slash == ft_strlen(cmd))
		return (2);
	if (access(cmd, F_OK | X_OK) == 0)
		return (3);
	return (0);
}

static int	ft_message_directory(char *cmd)
{
	char	*str;
	char	*tmp;
	int		ck;

	ck = ft_check_cmd(cmd);
	if (ck == 1 || ck == 3)
	{
		str = ft_strjoin("bash: ", cmd);
		if (!str)
		{
			write(2, "ft_strjoin: error malloc\n", 26);
			return (1);
		}
		tmp = str;
		str = ft_strjoin(str, ": Is a directory\n");
		free(tmp);
		if (!str)
		{
			write(2, "ft_strjoin: error malloc\n", 26);
			return (1);
		}
		write(2, str, ft_strlen(str));
		return (free(str), 1);
	}
	return (0);
}

void	ft_perr(int err, char *cmd)
{
	char	*str;
	int		ck;

	if (err == E_NO_CMD)
	{
		ck = ft_message_directory(cmd);
		if (ck == 1)
			return ;
		else if (ck_char(cmd, '/') > 0)
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
