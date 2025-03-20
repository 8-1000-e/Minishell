/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:13:37 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/11 12:56:31 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	next_w(char **str, int *iq, int *idq)
{
	char	*s;
	int		i;

	i = 0;
	s = *str;
	while (*s && s[i])
	{
		if (s[i] == '"' && *iq == 0 && ((i == 0) || (i > 0 && s[i - 1] != '\\'))
			&& *idq == 0)
		{
			*idq = 1;
			break ;
		}
		else if (s[i] == '\'' && *idq == 0 && ((i == 0)
				|| (i > 0 && s[i - 1] != '\\')) && *iq == 0)
		{
			*iq = 1;
			break ;
		}
		if (s[i] != ' ' && !*idq && !*iq)
			break ;
		i++;
	}
	*str = s + i;
}

char	**split(char *word, int idq, int iq, char *str)
{
	char	**tab;

	tab = NULL;
	while (str && *str)
	{
		next_w(&str, &iq, &idq);
		if (!iq && !idq && *str == '|' && *str++)
			ft_strapp(&tab, ft_strdup("|"));
		else if (*str)
		{
			word = ft_calloc(ft_strlen(str) + 1, 1);
			if (!word)
				return (NULL);
			if ((idq || iq) && str++)
				add_quoted_word(&word, &str, &idq, &iq);
			else
				add_simple_word(&word, &str);
			ft_strapp(&tab, word);
			if (*str == '|' && *str++)
				ft_strapp(&tab, ft_strdup("|"));
		}
	}
	return (tab);
}

char	*dup_char(char c, int size)
{
	char	*dup;
	char	*save;

	dup = ft_calloc(1, size + 1);
	save = dup;
	if (!dup)
		return (NULL);
	while (--size >= 0)
		*save++ = c;
	return (dup);
}

char	**ft_ms_split(char *str, int *quote_pb)
{
	char	**tab;
	char	*word;
	int		idq;
	int		iq;

	tab = NULL;
	iq = 0;
	idq = 0;
	word = NULL;
	*quote_pb = check_quote(str);
	if (!*quote_pb)
		tab = split(word, idq, iq, str);
	tab = manage_dir(tab, '>');
	tab = manage_dir(tab, '<');
	return (tab);
}
