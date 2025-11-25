/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/23 10:06:51 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_dot_command(char **args)
{
	if (ft_strcmp(args[0], ".") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(".: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		return (2);
	}
	if (args[0][0] == '.' && args[0][1] == '.')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	return (0);
}

int	execute_builtin_safe(char **args, t_env *env)
{
	int	builtin_result;

	builtin_result = execute_builtin(args, env);
	if (g_signal_status >= 256)
		return (g_signal_status);
	g_signal_status = builtin_result;
	return (g_signal_status % 256);
}

int	execute_ast_child(t_ast_node *node, t_env *env)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		g_signal_status = execute_command_child(node, env);
	else if (node->type == NODE_PIPE)
		g_signal_status = execute_pipe(node, env);
	else
		g_signal_status = 1;
	return (g_signal_status % 256);
}

int	setup_command_redirections(t_ast_node *node, t_env *env)
{
	env->saved_stdin = dup(STDIN_FILENO);
	env->saved_stdout = dup(STDOUT_FILENO);
	if (env->saved_stdin == -1 || env->saved_stdout == -1)
	{
		close_fd(env->saved_stdin, env->saved_stdout);
		return (1);
	}
	if (setup_redirections(node->redirects, env) != 0)
	{
		restore_std_fds(env->saved_stdin, env->saved_stdout);
		return (1);
	}
	return (0);
}

void	update_exit_status(int result)
{
	if (result >= 256)
		g_signal_status = result;
	else if (g_signal_status < 256)
		g_signal_status = result;
}
