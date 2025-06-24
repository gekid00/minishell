/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/23 10:07:01 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(pid_t pid, t_env *env)
{
	int	status;

	(void)env;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_signal_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal_status = 128 + WTERMSIG(status);
}

void	handle_command_not_found(t_ast_node *node)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	g_signal_status = 127;
	setup_signals();
}

void	execute_fork_process(t_child_data *child_data, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_child_data(child_data);
		return ;
	}
	if (pid == 0)
		minimal_child_process(child_data, env);
	else
	{
		free_child_data(child_data);
		parent_process(pid, env);
	}
}
