/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:33:16 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 09:54:26 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	ft_init_struct(t_pipex *p)
{
	p->good_path = NULL;
	p->cmd_opt = NULL;
	p->fd_p = NULL;
	p->name_here_doc = NULL;
}

static void	ft_parse(int ac, char **av, char **env, t_pipex *p)
{
	if (ac < 5)
		(write(2, "At least 4 arguments needed\n", 28), exit(EXIT_FAILURE));
	p->prompt = 0;
	ft_init_struct(p);
	if (ac > 5 && ft_strcmp(av[1], "here_doc") == 0)
		ft_prompt(av, p);
	else if (ft_strcmp(av[1], "here_doc") == 0)
		(write(2, "At least 5 arguments needed\n", 28), exit(EXIT_FAILURE));
	p->path = ft_research_path(env);
}

static void	ft_create_fd_p(int size, t_pipex *p)
{
	int	j;

	j = -1;
	p->fd_p = (int **)malloc(sizeof(int *) * (size));
	if (!p->fd_p)
		(perror("malloc: error"), ft_exit(p, -1, -1, -1));
	while (++j < size - 1)
	{
		p->fd_p[j] = (int *)malloc(sizeof(int) * 2);
		if (!p->fd_p)
			(perror("malloc: error"), ft_exit(p, -1, -1, j));
	}
	p->fd_p[size - 1] = NULL;
}

static void	ft_pipex(int ac, char **av, t_pipex *p)
{
	t_index	index;

	index.i = 1;
	index.j = 0;
	ft_create_fd_p(ac - 3 - p->prompt, p);
	while (++index.i + p->prompt < ac - 2)
	{
		if (pipe(p->fd_p[index.j]) == -1)
		{
			(perror("pipe"));
			if (index.j > 0)
				close(p->fd_p[index.j - 1][0]);
			return ;
		}
		if (index.i == 2)
			ft_first_pipe(av, *p);
		else if (index.i + p->prompt >= 2)
			ft_middle_pipe(av, *p, index.j);
		index.j++;
	}
	ft_last_pipe(av, *p, index.j);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;

	p.prompt = 0;
	ft_parse(ac, av, env, &p);
	ft_pipex(ac, av, &p);
	while (wait(NULL) > 0)
		;
	if (p.path)
		ft_free_split(p.path);
	ft_free_fd_p(p.fd_p, -1);
	if (p.name_here_doc)
	{
		unlink(p.name_here_doc);
		free(p.name_here_doc);
	}
	exit(0);
}
