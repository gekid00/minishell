/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basic_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 00:14:30 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_n_option(char **args)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		n = 1;
		i++;
	}
	return (i * 1000 + n);
}

void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args, t_env *env)
{
	(void)env;
	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		g_signal_status = 256;
		return (0);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_signal_status = 256 + 2;
		return (2);
	}
	if (args[2])
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	g_signal_status = ft_atoi(args[1]);
	g_signal_status = ((g_signal_status % 256) + 256) % 256;
	g_signal_status = 256 + g_signal_status;
	return (g_signal_status % 256);
}
