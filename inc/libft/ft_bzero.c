/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:12:38 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 19:46:54 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* @brief Sets a given string to '\0'
	@param s The string to be set to '\0'
	@param n The size of the string
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*b;
	int				c;

	b = s;
	c = '\0';
	while (n > 0)
	{
		*b = c;
		b++;
		n--;
	}
}
