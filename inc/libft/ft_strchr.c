/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:45:40 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/10 19:43:39 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/* @brief Looks for a character inside a string,
returns NULL if c is not contained within the string.
If the character is found, returns pointer to the first instance
of the character.

 @param *s String to search
 @param c Character to look for */
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && ((unsigned char)c) != *s)
		s++;
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (NULL);
}
