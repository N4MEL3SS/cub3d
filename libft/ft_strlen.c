/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celadia <celadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:30:21 by celadia           #+#    #+#             */
/*   Updated: 2022/08/15 14:30:21 by celadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char		*check = s;
	const size_t	mask = 0x7F7F7F7F7F7F7F7F;

	while ((size_t)check & 0b111)
		if (!*check++)
			return (check - s - 1);
	while (~(((*(size_t *)check & mask) + mask) | *(size_t *)check | mask) == 0)
		check += 8;
	if (!check[0])
		return (check - s);
	else if (!check[1])
		return (check - s + 1);
	else if (!check[2])
		return (check - s + 2);
	else if (!check[3])
		return (check - s + 3);
	else if (!check[4])
		return (check - s + 4);
	else if (!check[5])
		return (check - s + 5);
	else if (!check[6])
		return (check - s + 6);
	else
		return (check - s + 7);
}
