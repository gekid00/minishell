/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/21 00:57:12 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_accessible_path(char *cmd, struct stat *path_stat)
{
	if (S_ISDIR(path_stat->st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		g_signal_status = 126;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		g_signal_status = 126;
	}
}

void	handle_direct_path_error(char *cmd)
{
	struct stat	path_stat;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &path_stat) == 0)
			handle_accessible_path(cmd, &path_stat);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_signal_status = 127;
	}
}
