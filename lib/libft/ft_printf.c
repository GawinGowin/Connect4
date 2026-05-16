/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:05:57 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 16:12:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

int ft_printf(const char *fmt, ...) {
  va_list args;
  int cnt;

  va_start(args, fmt);
  cnt = ft_vdprintf(STDOUT_FILENO, fmt, args);
  va_end(args);
  return (cnt);
}
