#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

#include "RPN.h"
#include "calc.h"
#include "defines.h"
#include "structs.h"

double calculate_is(char *string, double j) {
  //    char *test = input_str();  //  считывание и сохранение строки
  Queue *q = rpn_translation(string);
  //    Grid *g;
  //    g = Grid_new(25, 80);
  //    Grid_clear(g);
  //    for (int x = 0; x < g->w; x++) {
  //        double j = 1;
  //    CEXCEPTION_T e;
  //    Try
  //    {
  //    double i = calculate(j, clone_queue(q));
  //    return i;
  //    }
  //    Catch(e)
  //    {

  //        switch (e)
  //        {
  //            case 1:
  //                printf("Алё, ты делишь на 0, чувак...");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //            case 2:
  //                printf("В ctg(...) присутствует деление на 0");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //            case 3:
  //                printf("В acos(...) число < -1, либо > 1");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //            case 4:
  //                printf("В asin(...) число < -1, либо > 1");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //            case 5:
  //                printf("После mod 0");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //            case 6:
  //                printf("Число слева от mod не целое =(");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //            case 7:
  //                printf("Число справа от mod не целое =(");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //            case 8:
  //                printf("Числа справа и слева от mod не целые =(");
  //                ui->pushButton_equal->setChecked(false);
  //                break;
  //        }
  //    }
  //        i = i * 21 + 3 + (1 - i) * 10;
  //        int y = round(i);
  //        if (y >= 0 && y <= 24)
  //            sustain(g, x, y);}
  //    Grid_print(g);
  //    Grid_free(g);
  double i = calculate(j, clone_queue(q));
  kill_queue(q);
  return i;
}

// char *input_str() {
//     char *string = malloc(sizeof(char));
//     int c = getchar();
//     int i = 0;
//     while (c != EOF && c != '\n') {
//         char *new = realloc(string, sizeof(char) * (i + 2));
//         if (new == NULL) {
//             free(string);
//         } else {
//             string[i] = c;
//             c = getchar();
//             i++;
//         }
//     }
//     string[i] = 0;
//     return string;
// }

// Grid *Grid_new(int h, int w) {
//     Grid *g = malloc(sizeof(Grid));
//     if (!g) return NULL;
//     g->w = w;
//     g->h = h;
//     g->cells = malloc(sizeof(Cell) * w * h);
//     if (!g->cells) {
//         free(g);
//         return NULL;
//     }
//     return g;
// }
// /* Почистить зарезервированую память. */
// void Grid_clear(Grid *g) {
//     int x, y;
//     for (x = 0; x < g->w; x++) {
//         for (y = 0; y < g->h; y++)
//             kill(g, x, y);
//     }
// }
// /* Обнулить точки на координатной плоскости. */
// void kill(Grid *g, int x, int y) {
//     Grid_get_cell(g, x, y)->function = false;
// }
// /* Точки на координатной плоскости. */
// Cell *Grid_get_cell(Grid *g, int x, int y) {
//     return &(g->cells[y * g->w + x]);
// }
// /* Статус точки. */
// boolean function(Grid *g, int x, int y) {
//     return Grid_get_cell(g, x, y)->function;
// }
// /* Активация точки графика функции. */
// void sustain(Grid *g, int x, int y) {
//     Grid_get_cell(g, x, y)->function = true;
// }
// void Grid_print(Grid *g) { /* Печатает функцию. */
//     int x, y;
//     for (y = 0; y < g->h; y++) {
//         for (x = 0; x < g->w; x++) {
//             if (function(g, x, y))
//                 printf("*");
//             else
//                 printf(".");
//         }
//         printf("\n");
//   }
// }
// /* Освободить динамическую память. */
// void Grid_free(Grid *g) {
//     free(g->cells);
//     free(g);
// }
