/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:33:16 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 09:51:28 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	ft_init_struct(t_pipex *p)
{
	p->good_path = NULL;
	p->cmd_opt = NULL;
}

static void	ft_parse(int ac, char **env, t_pipex *p)
{
	if (ac != 5)
		(write(2, "At least 4 arguments needed\n", 28), exit(EXIT_FAILURE));
	ft_init_struct(p);
	p->path = ft_research_path(env);
}

static void	ft_pipex(char **av, t_pipex *p)
{
	if (pipe(p->fd_p) == -1)
		return ;
	ft_first_pipe(av, *p, 2);
	ft_last_pipe(av, *p, 3);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;

	ft_parse(ac, env, &p);
	ft_pipex(av, &p);
	while (wait(NULL) > 0)
		;
	if (p.path)
		ft_free_split(p.path);
	exit(0);
}
