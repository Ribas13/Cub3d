/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:14:33 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 19:54:14 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

/* @brief Checks if a character is printable
	@param c The character to be checked
	@result Returns 1 if the character is printable, 0 if not
 */
int	ft_isprint(int c)
{
	if (!((c < 0) || (c >= 0 && c <= 31) || (c >= 127)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*
int	main(void)
{
	printf("mine : %i\n", ft_isprint('\200'));
}*/
