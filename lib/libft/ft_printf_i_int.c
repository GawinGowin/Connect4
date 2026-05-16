/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _i_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:35 by saraki            #+#    #+#             */
/*   Updated: 2023/08/19 18:27:49 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

int	i_print_dec(int fd, va_list args)
{
	int				value;
	int				digits;
	unsigned int	uint_value;
	uintptr_t		ulong_value;

	value = va_arg(args, int);
	digits = 0;
	if (value < 0)
	{
		uint_value = (unsigned int)(-1 * value);
		if (write(fd, "-", 1) != -1)
			digits += 1;
	}
	else
		uint_value = value;
	ulong_value = (uintptr_t) uint_value;
	digits += dec_to_nbase(ulong_value, "0123456789", fd);
	return (digits);
}

// int	test_helper(const char *fmt, ...)
// {
// 	va_list		args;
// 	uintptr_t	value;
// 	int			len;

// 	va_start(args, fmt);
// 	len = i_print_dec(args);
// 	va_end(args);
// 	return (len);
// }

// #include <stdio.h>
// int	main(void)
// {
// 	int		len;

// 	len = test_helper("", 2147483647);
// 	printf("\n%d\n", len);
// 	len = printf("%i", 2147483647);
// 	printf("\n%d\n", len);

// 	len = test_helper("", -2147483648);
// 	printf("\n%d\n", len);
// 	len = printf("%i", -2147483648);
// 	printf("\n%d\n", len);

// 	len = test_helper("", -100);
// 	printf("\n%d\n", len);
// 	len = printf("%i", -100);
// 	printf("\n%d\n", len);
// }
