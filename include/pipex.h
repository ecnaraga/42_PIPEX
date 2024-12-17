/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:50:13 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 09:56:52 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/ft_printf/include/ft_printf.h"
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

enum		e_err
{
	E_OK,
	E_STRJOIN,
	E_STRDUP,
	E_NO_CMD
};

typedef struct s_pipex
{
	int		fd_p[2];
	char	**path;
	char	*good_path;
	char	**cmd_opt;
}			t_pipex;

/*error.c*/
void		ft_perr(int err, char *cmd);
void		ft_exit(t_pipex *p, int fd_1, int fd_2);

/*pipex.c*/
void		ft_first_pipe(char **av, t_pipex p, int i);
void		ft_last_pipe(char **av, t_pipex p, int i);

/*pipex_utils.c*/
void		redef_stdin(char **av, t_pipex p);
void		redef_stout(char **av, t_pipex p, int *fd_outfile);
int			ft_access_cmd(char **path, char *cmd, char **good_path);
char		**ft_research_path(char **env);

#endif