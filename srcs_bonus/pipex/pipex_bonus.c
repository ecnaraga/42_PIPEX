/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:01:52 by garance           #+#    #+#             */
/*   Updated: 2023/09/21 09:57:20 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	ft_child_exec(t_pipex p, char **av, int i)
{
	int	err;

	err = ft_access_cmd(p.path, p.cmd_opt[0], &p.good_path);
	if (err > 0)
		(ft_perr(err, av[i]), ft_exit(&p, -1, -1, -1));
	execve(p.good_path, p.cmd_opt, NULL);
	(perror("execve1"), ft_exit(&p, -1, -1, -1));
}

static void	ft_parent(pid_t pid, int fd_1, int fd_2)
{
	if (pid != 0)
	{
		if (fd_1 > -1)
			close(fd_1);
		if (fd_2 > -1)
			close(fd_2);
	}
}

void	ft_first_pipe(char **av, t_pipex p)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(p.fd_p[0][0]);
		redef_stdin(av, p);
		if (dup2(p.fd_p[0][1], STDOUT_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, p.fd_p[0][1], -1, -1));
		close(p.fd_p[0][1]);
		p.cmd_opt = ft_split_iss(av[2 + p.prompt]);
		if (!p.cmd_opt)
			(write(2, "ft_split_iss: error\n", 21), ft_exit(&p, -1, -1, -1));
		if (!p.cmd_opt[0])
			(ft_perr(E_NO_CMD, av[2 + p.prompt]), ft_exit(&p, -1, -1, -1));
		ft_child_exec(p, av, 2 + p.prompt);
	}
	ft_parent(pid, p.fd_p[0][1], -1);
}

void	ft_middle_pipe(char **av, t_pipex p, int j)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(p.fd_p[j][0]);
		if (dup2(p.fd_p[j - 1][0], STDIN_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, p.fd_p[j - 1][0], p.fd_p[j][1], -1));
		close(p.fd_p[j - 1][0]);
		if (dup2(p.fd_p[j][1], STDOUT_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, p.fd_p[j][1], -1, -1));
		close(p.fd_p[j][1]);
		p.cmd_opt = ft_split_iss(av[2 + j + p.prompt]);
		if (!p.cmd_opt)
			(write(2, "ft_split_iss: error\n", 21), ft_exit(&p, -1, -1, -1));
		if (!p.cmd_opt[0])
			(ft_perr(E_NO_CMD, av[2 + j + p.prompt]), ft_exit(&p, -1, -1, -1));
		ft_child_exec(p, av, 2 + j + p.prompt);
	}
	ft_parent(pid, p.fd_p[j - 1][0], p.fd_p[j][1]);
}

void	ft_last_pipe(char **av, t_pipex p, int j)
{
	pid_t	pid;
	int		fd_outfile;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (dup2(p.fd_p[j - 1][0], STDIN_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, p.fd_p[j - 1][0], -1, -1));
		close(p.fd_p[j - 1][0]);
		redef_stout(av, p, &fd_outfile, j);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, fd_outfile, -1, -1));
		close(fd_outfile);
		p.cmd_opt = ft_split_iss(av[2 + j + p.prompt]);
		if (!p.cmd_opt)
			(write(2, "ft_split_iss: error\n", 21), ft_exit(&p, -1, -1, -1));
		if (!p.cmd_opt[0])
			(ft_perr(E_NO_CMD, av[2 + j + p.prompt]), ft_exit(&p, -1, -1, -1));
		ft_child_exec(p, av, 2 + j + p.prompt);
	}
	ft_parent(pid, p.fd_p[j - 1][0], -1);
}
