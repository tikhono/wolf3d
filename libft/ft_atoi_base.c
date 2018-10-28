/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:26:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/05/11 16:39:02 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_base(const char *s, int base)
{
	size_t		i;
	size_t		res;
	int			symbol;

	i = 0;
	while ((s[i] >= 0 && s[i] <= 20) || s[i] == ' ')
		++i;
	res = 0;
	symbol = 1;
	if (s[i] == '-')
		symbol = -1;
	if (s[i] == '-' || s[i] == '+')
		++i;
	if (base == 16)
		i += 2;
	while ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'F'))
	{
		res = res * base + ((s[i] >= 'A') ? s[i++] - 'A' + 10 : s[i++] - '0');
		if (res > 9223372036854775807U && symbol == 1)
			return (-1);
		if (res > 9223372036854775808U && symbol == -1)
			return (0);
	}
	return ((int)(res) * symbol);
}
