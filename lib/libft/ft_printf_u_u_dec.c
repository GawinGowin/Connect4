/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _u_u_dec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:45 by saraki            #+#    #+#             */
/*   Updated: 2023/08/19 18:28:04 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

int	u_print_dec(va_list args)
{
	int				digits;
	unsigned int	value;
	uintptr_t		ulong_value;

	value = va_arg(args, unsigned int);
	ulong_value = (uintptr_t) value;
	digits = dec_to_nbase(ulong_value, "0123456789", STDOUT_FILENO);
	return (digits);
}

// int	test_helper(const char *fmt, ...)
// {
// 	va_list		args;
// 	uintptr_t	value;
// 	int			len;

// 	va_start(args, fmt);
// 	len = u_print_dec(args);
// 	va_end(args);
// 	return (len);
// }

// #include <stdio.h>
// int	main(void)
// {
// 	int		len;

// 	len = test_helper("", 4294967295);
// 	printf("\n%d\n", len);
// 	len = printf("%u", 4294967295);
// 	printf("\n%d\n", len);

// 	len = test_helper("", 0);
// 	printf("\n%d\n", len);
// 	len = printf("%u", 0);
// 	printf("\n%d\n", len);

// 	len = test_helper("", 4294967295 + 1);
// 	printf("\n%d\n", len);
// 	len = printf("%u", 4294967295 + 1);
// 	printf("\n%d\n", len);

// 	len = test_helper("", 5000);
// 	printf("\n%d\n", len);
// 	len = printf("%u", 5000);
// 	printf("\n%d\n", len);
// }
