/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:28:00 by juliensarda       #+#    #+#             */
/*   Updated: 2024/01/25 13:54:59 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*sj;
	int		n;
	int		n1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1);
	n1 = ft_strlen(s2);
	sj = (char *)malloc((sizeof(char) * n) + (sizeof(char) * n1) + 2);
	if (!sj)
		return (NULL);
	while (s1[i] != '\0')
		sj[j++] = s1[i++];
	i = 0;
	sj[j++] = ' ';
	while (s2[i] != '\0')
		sj[j++] = s2[i++];
	sj[j] = '\0';
	return (free(s1), sj);
}
