/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:17:31 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 08:37:11 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_overflow(long num, char digit, int *error)
{
	if (num > LONG_MAX / 10
		|| (num == LONG_MAX / 10 && digit - '0' > LONG_MAX % 10))
	{
		*error = 1;
		return (1);
	}
	if (num < LONG_MIN / 10
		|| (num == LONG_MIN / 10 && digit - '0' > -(LONG_MIN % 10)))
	{
		*error = 1;
		return (1);
	}
	return (0);
}

int	make_conversion(long *num, char **num_str, int *error)
{
	if (!ft_isdigit(**num_str))
	{
		*error = 1;
		return (0);
	}
	*error = 0;
	if (check_overflow(*num, **num_str, error))
		return (0);
	*num = *num * 10 + (**num_str - '0');
	*(num_str) += 1;
	return (1);
}

long	str_to_long(char *num_str, int *error)
{
	long	num;
	int		is_negative;

	num = 0;
	is_negative = 0;
	if (*num_str == '-')
	{
		is_negative = 1;
		num_str++;
	}
	else if (*num_str == '+')
		num_str++;
	while (*num_str)
	{
		if (!make_conversion(&num, &num_str, error))
			return (0);
	}
	if (is_negative)
		num = -num;
	return (num);
}
