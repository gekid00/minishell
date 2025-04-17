/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:15:10 by gekido            #+#    #+#             */
/*   Updated: 2025/04/18 00:24:32 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_exit(void)
{
	if (g_signal_status >= 256)
		return (1);
	return (0);
}

int	get_exit_code(void)
{
	if (g_signal_status >= 256)
		return (g_signal_status % 256);
	return (0);
}

int	process_input(char *input, t_env *env)
{
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	handle_command(input, env);
	free(input);
	if (g_signal_status >= 256)
		return (0);
	return (1);
}

void	close_fd(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}
