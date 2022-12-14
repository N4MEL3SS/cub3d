/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celadia <celadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:32:35 by celadia           #+#    #+#             */
/*   Updated: 2022/08/15 14:32:35 by celadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_assign_ptr(void **dst_ptr, void *src_ptr)
{
	*dst_ptr = src_ptr;
	return (*dst_ptr);
}
