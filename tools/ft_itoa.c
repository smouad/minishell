/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:09:27 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 19:49:22 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	nbr_len(int nbr)
{
	int	i;

	i = 0;
	if (nbr <= 0)
		i = 1;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = nbr_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[len] = ft_abs(n % 10) + '0';
		n = ft_abs(n / 10);
		len--;
	}
	return (str);
}
