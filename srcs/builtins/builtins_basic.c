/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:30:00 by gekido            #+#    #+#             */
/*   Updated: 2025/04/12 14:56:03 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_builtin(char **args, t_env *env)
{
	char	*path;
	char	cwd[1024];

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value("HOME", env);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	if (getcwd(cwd, 1024))
		update_env_var(env, "PWD", cwd);
	return (0);
}

int	echo_builtin(char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args)
{
	int	exit_code;

	ft_putendl_fd("exit", 1);
	if (!args[1])
		exit(g_signal_status);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	exit_code = ft_atoi(args[1]) % 256;
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit(exit_code);
	return (0);
}

int	pwd_builtin(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		ft_putendl_fd("pwd: error retrieving current directory", 2);
		return (1);
	}
}
