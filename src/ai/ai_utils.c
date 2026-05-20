#include "connect4.h"

int build_order_array(int *array, int cols, int max_cols) {
  if (cols > max_cols) {
    return -1;
  }
  int center = cols / 2;
  array[0] = center;
  int i = 1;
  for (int d = 1; d <= cols; d++) {
    if (center - d >= 0) {
      array[i++] = center - d;
    }
    if (center + d < cols) {
      array[i++] = center + d;
    }
  }
  return (i);
}
