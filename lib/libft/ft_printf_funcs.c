/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:31:21 by saraki            #+#    #+#             */
/*   Updated: 2023/10/01 05:29:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"
#include "libft_int.h"

t_func_pt	switch_fmt_render(char specifier)
{
	if (specifier == 'c')
		return ((t_func_pt) c_print_char);
	else if (specifier == 's')
		return ((t_func_pt) s_print_str);
	else if (specifier == 'p')
		return ((t_func_pt) p_print_pt);
	else if (specifier == 'd')
		return ((t_func_pt) d_print_dec);
	else if (specifier == 'i')
		return ((t_func_pt) i_print_dec);
	else if (specifier == 'u')
		return ((t_func_pt) u_print_dec);
	else if (specifier == 'x')
		return ((t_func_pt) x_print_dec_lower);
	else if (specifier == 'X')
		return ((t_func_pt) x_print_dec_upper);
	else if (specifier == '%')
		return ((t_func_pt) _print_percent);
	else
		return ((t_func_pt) _other_format);
}

int dec_to_nbase(uintptr_t n, char *base, int fd) {
  uintptr_t base_num;
  uintptr_t residual;
  int cnt;

  base_num = (uintptr_t)ft_strlen(base);
  if (n < base_num) {
    if (write(fd, &base[n], 1) == -1)
      return (0);
    return (1);
  }
  residual = n % base_num;
  cnt = dec_to_nbase(n / base_num, base, fd);
  if (write(fd, &base[residual], 1) == -1)
    return (cnt);
  return (cnt + 1);
}
