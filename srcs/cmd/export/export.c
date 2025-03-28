/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:23:05 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/26 14:05:08 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	export_add(t_data *data, char **key, char *cmd)
{
	t_env	*node;
	char	*value;

	if (!ft_strnstr(cmd, "+=", ft_strlen(cmd)))
		return (-1);
	node = ms_get_node_by_key(data, key[0]);
	if (!node)
		return (-1);
	value = ft_strjoin(node->value, key[1]);
	if (!ms_edit_env_lst(data, key[0], value,
			ft_buildstr("%s=%s", key[0], value)))
		return (0);
	return (1);
}

int	export_var(t_data *data, char **key, char *cmd)
{
	char	*var;
	int		exit_code;

	exit_code = export_add(data, key, cmd);
	if (exit_code >= 0)
		return (exit_code);
	if (!key[1] && !ms_get_node_by_key(data, key[0]))
	{
		if (!ms_new_var(&data->env_list, key[0], 0, ft_strdup(key[0])))
			return (0);
	}
	else if (key[1])
	{
		var = ft_buildstr("%s=%s", key[0], key[1]);
		if (!var)
		{
			ft_free_tab(key);
			return (0);
		}
		if (!ms_create_or_edit(data, key[0], key[1], var))
			return (0);
	}
	return (1);
}

void	ms_swap_node(char **char1, char **char2)
{
	char	*tmp;

	tmp = *char1;
	*char1 = *char2;
	*char2 = tmp;
}

int	ms_create_node_ifno(t_data *data, char *char1, t_env **node)
{
	*node = ms_get_node_by_key(data, char1);
	if (*node)
		return (1);
	if (!ms_new_var(&data->env_list, char1, 0, char1))
		return (-1);
	*node = ms_get_node_by_key(data, char1);
	if (!*node)
		return (0);
	return (1);
}

int	export(t_data *data, char **cmds)
{
	char	**key;
	int		exit_code;

	if (!cmds[1])
		return (ms_print_export(*data));
	while (*(++cmds))
	{
		key = ms_split_env(*cmds);
		if (!key)
			return (-1);
		if (!is_valid_key(key[0]) || !*key[0])
		{
			printf("bash: export: `%s': not a valid identifier\n", *cmds);
			exit_code = 1;
			ft_free_tab(key);
			continue ;
		}
		if (!export_var(data, key, *cmds))
			return (-1);
		exit_code = 0;
		dh_free(key);
	}
	if (!ms_build_array_env(data))
		return (-1);
	return (exit_code);
}
