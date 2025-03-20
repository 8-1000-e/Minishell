/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:56:25 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 14:32:59 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	fill_paths(t_data *data)
{
	int		j;
	char	*cmd_name;

	j = -1;
	while (data->cmd_list[++j].cmd)
	{
		assign_absolute_path(data, j);
		if (data->cmd_list[j].path)
			continue ;
		cmd_name = data->cmd_list[j].cmd[0];
		data->cmd_list[j].path = find_valid_path(data->paths, cmd_name);
	}
}

int	len_cmd(char **line)
{
	int	c;
	int	i;

	i = 0;
	c = 1;
	while (line[i])
	{
		if (line[i][0] == '|')
			c++;
		if (i > 0 && line[i - 1][0] == '|')
			c++;
		i++;
	}
	return (c);
}

void	fill_command(t_data *data, char **line)
{
	int	i;
	int	j;
	int	nb_cmd;

	nb_cmd = len_cmd(line);
	i = 0;
	j = 0;
	data->cmd_list = ft_calloc(nb_cmd + 1, sizeof(t_cmd));
	while (i < nb_cmd && data->cmd_list && line[j])
	{
		while (line[j] && line[j][0] != '|')
			ft_strapp(&data->cmd_list[i].cmd, line[j++]);
		if (line[j] && line[j][0] == '|' && !j)
			ft_strapp(&data->cmd_list[i].cmd, line[j++]);
		else if (line[j] && line[j][0] == '|')
			ft_strapp(&data->cmd_list[++i].cmd, line[j++]);
		i++;
	}
}

int	fill_line_data(t_data *data, char *line)
{
	char	**full_line;
	int		i;

	i = 0;
	collect_data(data);
	data->here_doc_name = NULL;
	if (!line)
		return (1);
	full_line = ft_ms_split(line, &i);
	if (i)
	{
		add_history(line);
		data->exit_status = 2;
		ft_printf(2, BOLD RED"/!\\ " BOLD BEIGE"Quote error !\n" RESET);
		ft_free_tab(full_line);
	}
	if (!full_line)
		exit_error(data, "failed malloc");
	else
		fill_data(data, full_line, line);
	return (i);
}
