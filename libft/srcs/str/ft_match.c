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

int		ft_match(const char *s1, const char *s2)
{
	if (s1[0] == '\0' && s2[0] == '\0')
		return (1);
	if (s2[0] == '*' && s2[1] == '\0')
		return (1);
	if (s1[0] == '\0' && s2[0] == '*')
		return (ft_match(s1, s2 + 1));
	if (s2[0] == '*')
		return (ft_match(s1, s2 + 1) || ft_match(s1 + 1, s2));
	if (s1[0] == s2[0])
		return (ft_match(s1 + 1, s2 + 1));
	return (0);
}
