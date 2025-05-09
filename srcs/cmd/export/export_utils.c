/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:48:42 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 14:10:03 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*ms_split_env_value(char *str, int i)
{
	char	*value;

	if (str[i] == '+')
		i++;
	if (!str[i + 1])
	{
		value = ft_strdup("");
		if (!value)
			return (0);
		return (value);
	}
	value = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (!value)
		return (0);
	return (value);
}

char	**ms_split_env(char *str)
{
	char	**tab;
	int		i;

	tab = ft_calloc(sizeof(char *), 3);
	if (!tab)
		return (0);
	i = 0;
	while (str[i] && !(str[i] == '+' && str[i + 1] == '=') && (str[i] != '='))
		i++;
	tab[0] = ft_substr(str, 0, i);
	if (!tab[0])
	{
		dh_free(tab);
		return (0);
	}
	if (!str[i])
		return (tab);
	tab[1] = ms_split_env_value(str, i);
	if (!tab[1])
	{
		ft_free_tab(tab);
		return (0);
	}
	return (tab);
}

char	*ms_get_env(t_data data, char *key)
{
	t_env	*tmp;

	tmp = data.env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

t_env	*ms_get_node_by_key(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = data->env_list;
	while (tmp && !ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (0);
}

int	ms_create_or_edit(t_data *data, char *key, char *value, char *str)
{
	if (ms_get_node_by_key(data, key))
	{
		if (!ms_edit_env_lst(data, key, value, str))
			return (0);
	}
	else
		if (!ms_new_var(&data->env_list, key, value, str))
			return (0);
	return (1);
}
