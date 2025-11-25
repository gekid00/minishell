/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:05:54 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 01:03:16 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_stop_word(char *input, int i)
{
	return (ft_is_space(input[i]) || input[i] == '|' || input[i] == '<'
		|| input[i] == '>' || input[i] == '\0');
}

void	handle_normal_text(char *input, int *i, char **word)
{
	char	*tmp;
	char	c[2];

	c[0] = input[*i];
	c[1] = '\0';
	tmp = ft_strjoin(*word, c);
	if (tmp)
	{
		free(*word);
		*word = tmp;
	}
	(*i)++;
}

void	extract_quoted_text(char *input, int *i, char **word, char quote)
{
	append_quote_to_word(word, quote);
	(*i)++;
	append_quoted_content(input, i, word, quote);
	if (input[*i] == quote)
	{
		append_quote_to_word(word, quote);
		(*i)++;
	}
}

char	*get_word(char *input, int *i)
{
	char	*word;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*i] && !should_stop_word(input, *i))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			handle_quotes(input, i, &word);
		else
			handle_normal_text(input, i, &word);
		if (!word)
			return (NULL);
	}
	return (word);
}
