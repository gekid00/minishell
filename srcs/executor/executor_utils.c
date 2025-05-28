/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:00:00 by rbourkai          #+#    #+#             */
/*   Updated: 2025/05/28 18:01:38 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**convert_env_to_array(t_env *env)
{
	return (env->vars);
}

void	child_process(t_ast_node *node, t_env *env)
{
	char	*path;

	path = find_path(node->args[0], env->vars);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(127);
	}
	if (execve(path, node->args, env->vars) == -1)
	{
		ft_putstr_fd("minishell: error executing: ", 2);
		ft_putendl_fd(node->args[0], 2);
		free(path);
		exit(126);
	}
	free(path);
	exit(1);
}

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
