/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:50:31 by lcuellar          #+#    #+#             */
/*   Updated: 2023/09/14 11:56:36 by lcuellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	chr;

	ptr = (unsigned char *)str;
	chr = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == chr)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
