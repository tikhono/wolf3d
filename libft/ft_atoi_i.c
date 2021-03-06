/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:26:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/11/12 13:11:41 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_i(const char *str, int *i)
{
	int		symbol;
	size_t	res;

	while ((str[*i] > 0 && str[*i] <= 20) || str[*i] == ' ')
		++(*i);
	res = 0;
	symbol = 1;
	if (str[*i] == '-')
		symbol = -1;
	if (str[*i] == '-' || str[*i] == '+')
		++(*i);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		res = res * 10 + str[*i] - '0';
		if (res > 9223372036854775807U && symbol == 1)
			return (-1);
		if (res > 9223372036854775808U && symbol == -1)
			return (0);
		++(*i);
	}
	res *= symbol;
	return ((int)res);
}
