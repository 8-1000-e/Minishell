/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:23:14 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/24 14:36:46 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_get_arg(char c_type, va_list args)
{
	if (c_type == 's')
		return (ft_strdup(va_arg(args, char *)));
	return ("");
}

static int	process_specifier(char *str, t_index *idx, char **build
				, va_list args)
{
	char	*arg;
	char	*segment;

	arg = ft_get_arg(str[idx->i + 1], args);
	segment = ft_substr(str, idx->start, idx->i - idx->start);
	*build = ft_strjoinfree(*build, segment, FREE_ALL);
	if (!*build)
		return (0);
	*build = ft_strjoinfree(*build, arg, FREE_ALL);
	if (!*build)
		return (0);
	idx->i++;
	idx->start = idx->i + 1;
	idx->i++;
	return (1);
}

char	*ft_buildstr(char *str, ...)
{
	t_index	idx;
	char	*build;
	va_list	args;

	build = ft_strdup("");
	if (!build)
		return (NULL);
	va_start(args, str);
	idx.i = 0;
	idx.start = 0;
	while (str[idx.i])
	{
		if (str[idx.i] == '%' && str[idx.i + 1])
		{
			if (!process_specifier(str, &idx, &build, args))
				break ;
		}
		else
			idx.i++;
	}
	build = ft_strjoinfree(build, ft_substr(str, idx.start, idx.i), FREE_ALL);
	va_end(args);
	return (build);
}
