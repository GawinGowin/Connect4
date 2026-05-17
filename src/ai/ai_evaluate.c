
#include "connect4.h"
#include "libft.h"

static int evaluate_window(t_cell player_mark, t_cell c0, t_cell c1, t_cell c2, t_cell c3);
static int count_in_window(t_cell target, t_cell c0, t_cell c1, t_cell c2, t_cell c3);

int ai_evaluate(t_board *b, t_cell player_mark) {
  t_cell c0, c1, c2, c3;
  int score = 0;

  int center = b->cols / 2;
  for (int row = 0; row < b->rows; row++) {
    for (int col = 0; col < b->cols; col++) {
      if (b->grid[row][col] == player_mark) {
        int dist = center - col;
        if (dist < 0)
          dist = -dist;
        score += (center - dist + 1);
      }
    }
  }

  // horizonal window check
  for (int row = 0; row < b->rows; row++) {
    for (int col = 0; col < b->cols - 3; col++) {
      c0 = b->grid[row][col];
      c1 = b->grid[row][col + 1];
      c2 = b->grid[row][col + 2];
      c3 = b->grid[row][col + 3];
      score += evaluate_window(player_mark, c0, c1, c2, c3);
    }
  }

  // vertical window check
  for (int col = 0; col < b->cols; col++) {
    for (int row = 0; row < b->rows - 3; row++) {
      c0 = b->grid[row][col];
      c1 = b->grid[row + 1][col];
      c2 = b->grid[row + 2][col];
      c3 = b->grid[row + 3][col];
      score += evaluate_window(player_mark, c0, c1, c2, c3);
    }
  }

  // positive diagonals window check
  for (int row = 0; row < b->rows - 3; row++) {
    for (int col = 0; col < b->cols - 3; col++) {
      c0 = b->grid[row][col];
      c1 = b->grid[row + 1][col + 1];
      c2 = b->grid[row + 2][col + 2];
      c3 = b->grid[row + 3][col + 3];
      score += evaluate_window(player_mark, c0, c1, c2, c3);
    }
  }

  // negative diagonals window check
  for (int row = 0; row < b->rows - 3; row++) {
    for (int col = 0; col < b->cols - 3; col++) {
      c0 = b->grid[row + 3][col];
      c1 = b->grid[row + 2][col + 1];
      c2 = b->grid[row + 1][col + 2];
      c3 = b->grid[row][col + 3];
      score += evaluate_window(player_mark, c0, c1, c2, c3);
    }
  }
  return score;
}

static int evaluate_window(t_cell player_mark, t_cell c0, t_cell c1, t_cell c2, t_cell c3) {
  int score = 0;
  t_cell opponent_mark = OPPONENT(player_mark);
  int my = count_in_window(player_mark, c0, c1, c2, c3);
  int opp = count_in_window(opponent_mark, c0, c1, c2, c3);
  int emp = count_in_window(CELL_EMPTY, c0, c1, c2, c3);

  if (my == 3 && emp == 1)
    score += 100;
  else if (my == 2 && emp == 2)
    score += 10;
  else if (my == 1 && emp == 3)
    score += 1;
  if (opp == 3 && emp == 1)
    score -= 100;
  else if (opp == 2 && emp == 2)
    score -= 10;
  return score;
}

static int count_in_window(t_cell target, t_cell c0, t_cell c1, t_cell c2, t_cell c3) {
  return (c0 == target) + (c1 == target) + (c2 == target) + (c3 == target);
}

// Ref: https://roboticsproject.readthedocs.io/en/latest/ConnectFourAlgorithm.html#analysis-functions
