/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 00:14:30 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_exit_status(char **result, int *i)
{
	char	*temp;

	temp = ft_itoa(g_signal_status % 256);
	if (temp)
	{
		*result = ft_strjoin_free(*result, temp);
		free(temp);
	}
	(*i)++;
}

void	handle_digit_variable(int *i)
{
	(*i)++;
}

void	handle_regular_variable(char *str, int *i, char **result, t_env *env)
{
	char	*var_name;

	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		append_to_result(result, '$');
	else
	{
		var_name = extract_var_name(str, i);
		if (var_name)
			process_var_expansion(var_name, result, env);
	}
}

void	update_quote_status(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
}
