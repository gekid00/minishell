/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:50:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/25 00:02:18 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exit_code(void)
{
	return (g_signal_status % 256);
}

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

int	is_unknown_cmd(t_token *tokens, t_env *env)
{
	char	*path;
	char	*cmd;

	cmd = tokens->value;
	path = find_path(cmd, env->vars);
	if (!path)
	{
		if (ft_strchr(cmd, '/') || ft_strncmp(cmd, "./", 2) == 0)
			handle_direct_path_error(cmd);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": command not found", 2);
			g_signal_status = 127;
		}
		return (1);
	}
	free(path);
	return (0);
}
