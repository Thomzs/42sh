/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/27 13:17:09 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *ps1;
	const unsigned char *ps2;

	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	if (s1 == s2 || !n)
		return (0);
	while ((*ps1 == *ps2) && --n)
	{
		ps1++;
		ps2++;
	}
	return ((int)(*ps1 - *ps2));
}
