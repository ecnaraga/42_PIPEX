/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:01:52 by garance           #+#    #+#             */
/*   Updated: 2023/09/21 10:11:41 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_child_exec(t_pipex p, char **av, int i)
{
	int	err;

	err = ft_access_cmd(p.path, p.cmd_opt[0], &p.good_path);
	if (err > 0)
		(ft_perr(err, av[i]), ft_exit(&p, -1, -1));
	execve(p.good_path, p.cmd_opt, NULL);
	(perror("execve1"), ft_exit(&p, -1, -1));
}

void	ft_first_pipe(char **av, t_pipex p, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(p.fd_p[0]);
		redef_stdin(av, p);
		if (dup2(p.fd_p[1], STDOUT_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, p.fd_p[1], -1));
		close(p.fd_p[1]);
		p.cmd_opt = ft_split_iss(av[2]);
		if (!p.cmd_opt)
			(write(2, "ft_split_iss: error\n", 21), ft_exit(&p, -1, -1));
		if (!p.cmd_opt[0])
			(ft_perr(E_NO_CMD, av[2]), ft_exit(&p, -1, -1));
		ft_child_exec(p, av, i);
	}
	if (pid != 0)
		close(p.fd_p[1]);
}

void	ft_last_pipe(char **av, t_pipex p, int i)
{
	pid_t	pid;
	int		fd_outfile;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (dup2(p.fd_p[0], STDIN_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, p.fd_p[0], -1));
		close(p.fd_p[0]);
		redef_stout(av, p, &fd_outfile);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			(perror("dup2"), ft_exit(&p, fd_outfile, -1));
		close(fd_outfile);
		p.cmd_opt = ft_split_iss(av[3]);
		if (!p.cmd_opt)
			(write(2, "ft_split_iss: error\n", 21), ft_exit(&p, -1, -1));
		if (!p.cmd_opt[0])
			(ft_perr(E_NO_CMD, av[3]), ft_exit(&p, -1, -1));
		ft_child_exec(p, av, i);
	}
	if (pid != 0)
		close(p.fd_p[0]);
}
