/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:53:14 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/08 21:12:03 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main()
{
	long long	i;

	i = -5000;
	i *= -1;
	if (i > 256)
		i %= 256;
	i = 256 - (i);
	printf("%lld\n", i);
}