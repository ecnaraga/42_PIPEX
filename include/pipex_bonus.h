/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:50:13 by galambey          #+#    #+#             */
/*   Updated: 2023/09/21 09:56:54 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/ft_printf/include/ft_printf.h"
# include "../libft/get_next_line/includes/get_next_line.h"
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

enum			e_err
{
	E_OK,
	E_STRJOIN,
	E_STRDUP,
	E_NO_CMD
};

typedef struct s_index
{
	int			i;
	int			j;
}				t_index;

typedef struct s_pipex
{
	int			**fd_p;
	char		**path;
	char		*good_path;
	char		**cmd_opt;
	char		*name_here_doc;
	short int	prompt;
}				t_pipex;

/*error.c*/
void			ft_perr(int err, char *cmd);
void			ft_exit(t_pipex *p, int fd_1, int fd_2, int j);

/*pipex.c*/
void			ft_first_pipe(char **av, t_pipex p);
void			ft_middle_pipe(char **av, t_pipex p, int j);
void			ft_last_pipe(char **av, t_pipex p, int j);

/*pipex_utils.c*/
void			redef_stdin(char **av, t_pipex p);
void			redef_stout(char **av, t_pipex p, int *fd_outfile, int j);
int				ft_access_cmd(char **path, char *cmd, char **good_path);
char			**ft_research_path(char **env);

/*prompt.c*/
void			ft_prompt(char **av, t_pipex *p);

/*main.c*/
void			ft_free_fd_p(int **fd_p, int j);

/*filename.c*/
void			create_here_doc(t_pipex *p);

#endif