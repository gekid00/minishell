/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:15:10 by gekido            #+#    #+#             */
/*   Updated: 2025/05/28 15:33:49 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_exit(t_env *env)
{
	if (env->signal_status >= 256)
		return (1);
	return (0);
}

int	get_exit_code(t_env *env)
{
	if (env->signal_status >= 256)
		return (env->signal_status % 256);
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
	if (env->signal_status >= 256)
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

int	is_unknown_cmd(t_token *tokens, t_env *env)
{
	char	*path;

	path = find_path(tokens->value, env->vars);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(tokens->value, 2);
		return (1);
	}
	free(path);
	return (0);
}
