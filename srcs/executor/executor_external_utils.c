/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/20 23:56:19 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_child_data(t_child_data *data)
{
	if (!data)
		return ;
	if (data->path)
		free(data->path);
	if (data->args)
		free_array(data->args);
	if (data->env_vars)
		free_array(data->env_vars);
	free(data);
}

void	handle_child_process(t_child_data *data)
{
	int	result;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(data->path, data->args, data->env_vars) == -1)
	{
		if (access(data->path, F_OK) == -1)
			result = 127;
		else if (access(data->path, X_OK) == -1)
			result = 126;
		else
			result = 127;
		free_child_data(data);
		exit(result);
	}
}

void	execute_child_process(t_child_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		handle_child_process(data);
	else if (pid > 0)
	{
		free_child_data(data);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_signal_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_signal_status = 128 + WTERMSIG(status);
	}
	else
	{
		free_child_data(data);
		g_signal_status = 1;
	}
}

char	**allocate_and_copy_args(char **node_args)
{
	char	**args;
	int		i;

	i = 0;
	while (node_args[i])
		i++;
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (node_args[i])
	{
		args[i] = ft_strdup(node_args[i]);
		if (!args[i])
		{
			while (i > 0)
				free(args[--i]);
			free(args);
			return (NULL);
		}
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_child_data	*init_child_data(void)
{
	t_child_data	*data;

	data = malloc(sizeof(t_child_data));
	if (!data)
		return (NULL);
	data->path = NULL;
	data->args = NULL;
	data->env_vars = NULL;
	return (data);
}
