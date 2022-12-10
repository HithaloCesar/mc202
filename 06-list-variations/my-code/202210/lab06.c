#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cobra.h"

/** @brief Snake game.
 *  @return Caso o programa seja executado com sucesso, retorna 0.
 */
int main(void) {
  int row_cnt, col_cnt;
  scanf("%d %d", &row_cnt, &col_cnt);
  p_matrix_char map = matrix_char_create(row_cnt, col_cnt);
  matrix_char_fill(map, '_');
  char command[6];
  p_coords_2d fruit = malloc(sizeof(struct coords_2d));
  fruit_insert(command, fruit, map);
  scanf("%s", command);
  p_dll_coords_2d snake = snake_insert(command, map);
  matrix_char_print(map);
  printf("\n");
  p_coords_2d dest = malloc(sizeof(struct coords_2d));
  bool resume = true;
  bool player_won = false;
  while (resume) {
    dest_coords_set(dest, snake, map);
    char dest_char = map->data[dest->row][dest->col];
    if (dest_char == '_')
      snake_move(snake, dest, map);
    else if (dest_char == '*') {
      snake_eat(snake, dest, map);
      if (snake->len == map->row_cnt * map->col_cnt) {
        resume = false;
        player_won = true;
      } else {
        matrix_char_print(map);
        printf("\n");
        fruit_insert(command, fruit, map);
      }
    } else if (dest_char == '#')
      resume = false;
    matrix_char_print(map);
    printf("\n");
  }
  if (player_won)
    printf("YOU WIN\n");
  else
    printf("GAME OVER\n");
  matrix_char_free(map);
  free(fruit);
  dll_coords_2d_free(snake);
  free(dest);
  return 0;
}
