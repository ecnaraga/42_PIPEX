/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:51:04 by garance           #+#    #+#             */
/*   Updated: 2023/09/21 09:54:20 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	create_here_doc(t_pipex *p)
{
	p->name_here_doc = ft_random_filename("/tmp/", 8);
	if (!p->name_here_doc)
	{
		p->name_here_doc = (char *)malloc(sizeof(char)
				* ft_strlen("/tmp/here_doc") + 1);
		if (!p->name_here_doc)
			(write(2, "malloc: error\n", 15), exit(EXIT_FAILURE));
		ft_strlcpy(p->name_here_doc, "/tmp/here_doc", 13 + 1);
	}
}
