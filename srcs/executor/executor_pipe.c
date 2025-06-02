/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/26 16:30:00 by gekido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_pipe(t_ast_node *node, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		saved_stdin;
	int		code;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execute_ast(node->left, env);
		code = g_signal_status;
		free_ast(node);
		free_env(env);
		_exit(code);
	}
	close(pipefd[1]);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (1);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	execute_ast(node->right, env);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
