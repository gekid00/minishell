/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/16 21:03:51 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_first_non_empty_token(t_token *tokens)
{
	t_token	*first_non_empty;

	first_non_empty = tokens;
	while (first_non_empty && first_non_empty->type == TOKEN_WORD
		&& (!first_non_empty->value || ft_strlen(first_non_empty->value) == 0))
		first_non_empty = first_non_empty->next;
	return (first_non_empty);
}

int	check_unknown_command(t_token *first_non_empty, t_env *env)
{
	if (first_non_empty && first_non_empty->type == TOKEN_WORD
		&& !is_builtin(first_non_empty->value))
	{
		if (is_unknown_cmd(first_non_empty, env))
			return (1);
	}
	return (0);
}

int	process_input(char *input, t_env *env)
{
	if (ft_strlen(input) == 0)
	{
		free(input);
		return (1);
	}
	handle_command(input, env);
	free(input);
	return (1);
}
