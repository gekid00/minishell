/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:09:20 by gekido            #+#    #+#             */
/*   Updated: 2025/05/03 17:49:24 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;
	int		match;

	i = 0;
	while (s[i])
	{
		match = 0;
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				match = 1;
				break ;
			}
			j++;
		}
		if (!match)
			break ;
		i++;
	}
	return (i);
}
