/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 01:03:16 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_skip_token(t_token *current, t_token *prev)
{
	if (prev && is_redirection(prev->type))
		return (1);
	if (!current->value || ft_strlen(current->value) == 0)
		return (1);
	return (0);
}

char	**free_args_on_error(char **args, int i)
{
	while (--i >= 0)
		free(args[i]);
	free(args);
	return (NULL);
}

static int	process_word_token(char **args, int *i, t_token *current,
			t_token *prev)
{
	if (should_skip_token(current, prev))
		return (0);
	args[*i] = ft_strdup(current->value);
	if (!args[*i])
		return (-1);
	(*i)++;
	return (1);
}

char	**extract_args_safe(t_token **token, int count)
{
	char	**args;
	int		i;
	t_token	*current;
	t_token	*prev;
	int		result;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	current = *token;
	prev = NULL;
	while (current && current->type != TOKEN_PIPE && i < count)
	{
		if (current->type == TOKEN_WORD)
		{
			result = process_word_token(args, &i, current, prev);
			if (result == -1)
				return (free_args_on_error(args, i));
		}
		prev = current;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}
