/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:17 by mgordag           #+#    #+#             */
/*   Updated: 2022/05/13 15:42:06 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!str)
		return (0);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	str[i] = '/';
	i++;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
