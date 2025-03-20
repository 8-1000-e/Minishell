/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:09:14 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/19 15:13:22 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*ms_get_key(char *str)
{
	int		size;
	char	*env;
	char	*save_env;
	char	*save_str;

	save_str = str;
	while (*str && is_env_char(*str))
		str++;
	size = str - save_str;
	env = dh_malloc(size + 1);
	if (!env)
		return (0);
	save_env = env;
	while (*save_str && is_env_char(*save_str))
		*env++ = *save_str++;
	*env = 0;
	return (save_env);
}

static char	*strinstr(char *src, int pos, char *dest)
{
	char	*str;

	str = ft_substr(src, 0, pos);
	str = ft_strjoinfree(str, dest, FREE_S1);
	pos++;
	while (is_env_char(src[pos]))
		pos++;
	str = ft_strjoinfree(str, src + pos, FREE_S1);
	return (str);
}

char	*replace_var_env(char *str, t_data data)
{
	char	*env;
	int		i;
	int		quote;
	int		dquote;

	quote = -1;
	dquote = -1;
	i = 0;
	(void)data;
	while (str && *(str + i))
	{
		check_quotes(str, i, &dquote, &quote);
		if (*(str + i) == '$' && *(str + i + 1) && is_env_char(*(str + i + 1))
			&& (quote == -1 || ((dquote < quote) && dquote != -1)))
		{
			env = ms_get_key(str + 1 + i);
			env = get_env(env, data);
			str = strinstr(str, i, env);
			i += ft_strlen(env);
		}
		else
			i++;
	}
	return (str);
}
