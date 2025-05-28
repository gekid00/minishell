/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:45:00 by rbourkai          #+#    #+#             */
/*   Updated: 2025/05/28 15:56:17 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_command_node(t_ast_node *node, t_env *env)
{
	if (node->redirects && setup_redirections(node->redirects) != 0)
		return (1);
	if (!node->args || !node->args[0])
		return (0);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args, env));
	else
	{
		execute_external_direct(node, env);
		return (127);
	}
}

int	handle_nested_pipe_child(t_ast_node *node, t_env *env, int *pipefd)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		exit(1);
	}
	close(pipefd[1]);
	exit(execute_left_side_direct(node->left, env));
}

int	handle_nested_pipe_parent(t_ast_node *node, t_env *env,
	int *pipefd, pid_t pid)
{
	int	status;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
		return (1);
	}
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	return (execute_left_side_direct(node->right, env));
}

int	handle_pipe_node(t_ast_node *node, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;

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
		handle_nested_pipe_child(node, env, pipefd);
	else
		return (handle_nested_pipe_parent(node, env, pipefd, pid));
	return (1);
}

int	execute_left_side_direct(t_ast_node *node, t_env *env)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (handle_command_node(node, env));
	else if (node->type == NODE_PIPE)
		return (handle_pipe_node(node, env));
	return (1);
}
