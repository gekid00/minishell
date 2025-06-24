/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:53:41 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/25 00:05:18 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	signal_hdl(int sig)
{
	(void)sig;
	g_signal_status = -1;
	printf("\r> ^C\n");
	close(STDIN_FILENO);
}

static int	heredoc_child_process(int *fd, t_redir *redir, t_env *env)
{
	char	*line;

	signal(SIGINT, signal_hdl);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	close(env->saved_stdin);
	close(env->saved_stdout);
	cleanup_child_process(env);
	if (g_signal_status == -1)
		exit(1);
	exit(0);
}

int	handle_heredoc(t_redir *redir, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (1);
	signal(SIGINT, sig_handler);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pid == 0)
		heredoc_child_process(fd, redir, env);
	sig_handler(-pid);
	close(fd[1]);
	waitpid(pid, &status, 0);
	sig_handler(SIGUSR1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (status);
}

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
