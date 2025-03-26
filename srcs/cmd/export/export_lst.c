/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:43:26 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 14:06:25 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_env	*ms_new_var(t_env **list, char *key, char *value, char *str)
{
	t_env	*new_var;

	if (!str)
		return (0);
	new_var = dh_malloc(sizeof(t_env));
	if (!new_var)
	{
		dh_free(str);
		dh_free(key);
		dh_free(value);
		return (0);
	}
	new_var->key = key;
	new_var->value = value;
	new_var->str = str;
	new_var->next = NULL;
	ms_add_lst(list, new_var);
	return (*list);
}

int	ms_size_lst_env(t_data *data, int is_export)
{
	t_env	*tmp;
	int		i;

	if (!data->env_list)
		return (0);
	tmp = data->env_list;
	i = 0;
	while (tmp)
	{
		if (is_export || tmp->value)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ms_edit_env_lst(t_data *data, char *key, char *value, char *str)
{
	t_env	*node;

	if (!key || !value || !str)
		return (0);
	node = ms_get_node_by_key(data, key);
	if (!node)
		return (0);
	dh_free(node->value);
	dh_free(node->str);
	node->value = value;
	node->str = str;
	dh_free(key);
	return (1);
}

t_env	*ms_setup_lst_env(t_data *data, char **env)
{
	int		i;
	char	**tab;
	t_env	*lst;

	i = 0;
	lst = NULL;
	while (env[i])
	{
		tab = ms_split_env(env[i]);
		if (!tab)
		{
			ms_free_lst_env(data);
			return (0);
		}
		lst = ms_new_var(&lst, tab[0], tab[1], ft_strdup(env[i]));
		dh_free(tab);
		i++;
	}
	data->env_list = lst;
	ms_build_array_env(data);
	return (lst);
}

void	ms_remove_env(t_data *data, char *key)
{
	t_env	*tmp;
	t_env	*before;

	tmp = data->env_list;
	before = tmp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			if (tmp == before)
				data->env_list = tmp->next;
			before->next = tmp->next;
			ms_free_env(tmp);
			return ;
		}
		before = tmp;
		tmp = tmp->next;
	}
}
