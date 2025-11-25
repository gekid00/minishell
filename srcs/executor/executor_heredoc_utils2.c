/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/21 00:57:12 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_heredoc_line(char *line, t_redir *redir, int original_stdin)
{
	if (!line)
	{
		if (g_signal_status == 130)
		{
			dup2(original_stdin, STDIN_FILENO);
			return (1);
		}
		return (2);
	}
	if (g_signal_status == 130)
	{
		free(line);
		dup2(original_stdin, STDIN_FILENO);
		return (1);
	}
	if (ft_strcmp(line, redir->file) == 0)
	{
		free(line);
		return (2);
	}
	return (0);
}

int	handle_heredoc_input(t_redir *redir, int fd, int original_stdin)
{
	char	*line;
	int		saved_status;
	int		check_result;

	saved_status = g_signal_status;
	g_signal_status = 0;
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		check_result = check_heredoc_line(line, redir, original_stdin);
		if (check_result == 1)
			return (1);
		if (check_result == 2)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	g_signal_status = saved_status;
	return (0);
}
