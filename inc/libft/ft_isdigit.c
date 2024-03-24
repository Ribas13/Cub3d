/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:13:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 19:53:31 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

/* @brief Checks if a character is a digit
	@param c The character to be checked
	@result Returns 1 if the character is a digit, 0 if not
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
		return (0);
}
/*
int	main(void)
{
	int	a;

	a = 'z';
	printf("is digit: %i", isdigit(a));
}*/
