/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:52:27 by dalebran          #+#    #+#             */
/*   Updated: 2023/10/18 09:59:16 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Concatenates the strings 's1' and 's2'.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = (char *)malloc(len_s1 + len_s2 + 1);
	if (!joined)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		joined[i] = s1[i];
	j = -1;
	while (++j < len_s2)
		joined[i++] = s2[j];
	joined[i] = '\0';
	return (joined);
}
