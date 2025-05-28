/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:00 by gekido            #+#    #+#             */
/*   Updated: 2025/05/28 15:56:17 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_pipe(t_ast_node *node, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		exit_status;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	if (pid == 0)
		execute_pipe_child(node, env, pipefd);
	exit_status = execute_pipe_parent(node, env, pipefd, pid);
	return (exit_status);
}

void	execute_pipe_child(t_ast_node *node, t_env *env, int *pipefd)
{
	int	exit_code;

	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		free_ast(node);
		free_env(env);
		exit(1);
	}
	close(pipefd[1]);
	exit_code = execute_left_side_direct(node->left, env);
	free_ast(node);
	free_env(env);
	exit(exit_code);
}

int	execute_pipe_parent(t_ast_node *node, t_env *env, int *pipefd, pid_t pid)
{
	int	status;
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	close(pipefd[1]);
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
