#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "CException.h"

QString str[255];
QString bracked = "(";
QString open[] = {"(",    "acos(", "asin(", "atan(", "tan(", "sin(",
                  "cos(", "ctg(",  "sqrt(", "log(",  "ln("};
QString digit[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
QString unary[] = {"-", "+"};
QString binary[] = {"-", "+", "/", "*", "^", "mod"};
int count = 0, index_num = 0, count_open = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(num()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_ctg, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(function()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(un_function()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(un_function()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(bi_function()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(bi_function()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(bi_function()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(bi_function()));
  ui->pushButton_equal->setCheckable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::num() {
  ui->Error->setText("");
  QPushButton *button = (QPushButton *)sender();
  if (count == 1 && ui->pushButton_equal->isChecked()) {
    ui->pushButton_equal->setChecked(false);
    for (int i = 0; i <= count; i++) str[i] = "";
    count = 0;
    index_num = 0;
    count_open = 0;
    str[count] = button->text();
    ui->result_show->setText(str[count]);
    count++;
  } else if (str[count - 1] != ")" && str[count - 1] != "x") {
    if (str[count - 1] == "0" &&
        count - 1 == index_num)  // проверка на то, что число начинается с 0
      ui->Error->setText("После нуля не может быть цыфр");
    else {
      QString num = "";
      str[count] = button->text();
      if (count ==
          index_num) {  // если у нас начало числа, то мы вводим любую цыфру
        for (int i = 0; i <= count; i++) num += str[i];
        ui->result_show->setText(num);
        count++;
      } else {
        for (int i = index_num; i <= count; i++) num += str[i];
        try {
          if (!num.toInt() && !num.contains('.')) throw 1;
          if (num.length() > 21 && num.contains('.')) throw 2;
          num = "";
          for (int i = 0; i <= count; i++) num += str[i];
          ui->result_show->setText(num);
          count++;
        } catch (int i) {
          str[count] = "";
          if (i == 1)
            ui->Error->setText(
                "Целое число не может быть меньше -2 147 483 648 и больше 2 "
                "147 483 647");
          else
            ui->Error->setText(
                "Дробное число не может быть длиньше 21 символа");
        }
      }
    }
  } else
    ui->Error->setText("Тут нельзя писать число");
}

void MainWindow::on_pushButton_all_del_clicked() {
  ui->pushButton_equal->setChecked(false);
  for (int i = 0; i <= count; i++) str[i] = "";
  count = 0;
  index_num = 0;
  count_open = 0;
  ui->result_show->setText("");
  ui->Error->setText("");
}

void MainWindow::on_pushButton_del_clicked() {
  ui->Error->setText("");
  if (ui->pushButton_equal->isChecked() && count == 1) {
    ui->pushButton_equal->setChecked(false);
    for (int i = 0; i <= count; i++) str[i] = "";
    count = 0;
    index_num = 0;
    count_open = 0;
    ui->result_show->setText("");
  } else {
    if (count == index_num) index_num--;
    if (count == 1) {
      count--;
      for (int i = 0; i < 11; i++)
        if (open[i] == str[count]) count_open--;
      str[count] = "";
      ui->result_show->setText("");
    } else if (count != 0) {
      count--;
      if (str[count] == ")") count_open++;
      for (int i = 0; i < 11; i++)
        if (open[i] == str[count]) count_open--;
      str[count] = "";
      QString string = "";
      for (int i = 0; i < count; i++) string += str[i];
      ui->result_show->setText(string);
    }
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  ui->Error->setText("");
  if (str[count - 1] == "0" && count - 1 == index_num) {
    str[count] = ".";
    count++;
    ui->result_show->setText(ui->result_show->text() + ".");
  } else {
    QString num = "";
    for (int i = index_num; i < count; i++) num += str[i];
    try {
      if (!num.toInt() && !num.contains(".")) throw 1;
      str[count] = ".";
      count++;
      ui->result_show->setText(ui->result_show->text() + ".");
    } catch (int i) {
      ui->Error->setText("Тут нельзя ставить точку");
    }
  }
}

void MainWindow::function() {
  QPushButton *button = (QPushButton *)sender();
  ui->Error->setText("");
  if (count == 1 && ui->pushButton_equal->isChecked()) {
    ui->pushButton_equal->setChecked(false);
    for (int i = 0; i <= count; i++) str[i] = "";
    count = 0;
    count_open = 1;
    str[count] = button->text() + "(";
    ui->result_show->setText(str[count]);
    count++;
    index_num = count;
  } else {
    if (count == 0) {
      str[count] = button->text() + "(";
      QString num = "";
      for (int i = 0; i <= count; i++) num += str[i];
      ui->result_show->setText(num);
      count++;
      index_num = count;
      count_open++;
    } else if (count > 0) {
      int flag = 0;
      for (int i = 0; i < 11; i++)
        if (open[i] == str[count - 1]) flag = 1;
      int is_binary = 0;
      for (int i = 0; i < 6; i++)
        if (binary[i] == str[count - 1]) is_binary = 1;
      if (is_binary || flag || count == 0) {
        str[count] = button->text() + "(";
        QString num = "";
        for (int i = 0; i <= count; i++) num += str[i];
        ui->result_show->setText(num);
        count++;
        index_num = count;
        count_open++;
      } else
        ui->Error->setText("Тут нельзя ввести функцию " + button->text());
    }
  }
}

void MainWindow::on_pushButton_x_clicked() {
  ui->Error->setText("");
  if (count == 1 && ui->pushButton_equal->isChecked()) {
    ui->pushButton_equal->setChecked(false);
    for (int i = 0; i <= count; i++) str[i] = "";
    count = 0;
    count_open = 0;
    str[count] = "x";
    ui->result_show->setText(str[count]);
    count++;
    index_num = count;
  } else if (count == 0) {
    str[count] = "x";
    count++;
    index_num = count;
    ui->result_show->setText(ui->result_show->text() + "x");
  } else if (count > 0) {
    int flag = 0;
    for (int i = 0; i < 11; i++)
      if (open[i] == str[count - 1]) flag = 1;
    int is_binary = 0;
    for (int i = 0; i < 6; i++)
      if (binary[i] == str[count - 1]) is_binary = 1;
    if (is_binary || flag || count == 0) {
      str[count] = "x";
      count++;
      index_num = count;
      ui->result_show->setText(ui->result_show->text() + "x");
    } else
      ui->Error->setText("Тут нельзя написать \"x\"");
  }
}

void MainWindow::on_pushButton_close_clicked() {
  ui->Error->setText("");
  if (count != 0) {
    int flag = 0;
    for (int i = 0; i < 10; i++)
      if (digit[i] == str[count - 1]) flag = 1;
    if ((str[count - 1] == "x" || str[count - 1] == ")" || flag) &&
        count_open > 0) {
      str[count] = ")";
      ui->result_show->setText(ui->result_show->text() + ")");
      count++;
      index_num = count;
      count_open--;
    } else if (count_open == 0)
      ui->Error->setText("Нету открывающей скобки");
    else
      ui->Error->setText("Сюда нельзя поставить закрывающую скобку");
  } else
    ui->Error->setText("Нельзя начать с закрывающей скобки");
}

void MainWindow::on_pushButton_open_clicked() {
  ui->Error->setText("");
  if (count == 1 && ui->pushButton_equal->isChecked()) {
    ui->pushButton_equal->setChecked(false);
    for (int i = 0; i <= count; i++) str[i] = "";
    count = 0;
    count_open = 1;
    str[count] = "(";
    ui->result_show->setText(str[count]);
    count++;
    index_num = count;
  } else if (count > 0) {
    int flag = 0;
    for (int i = 0; i < 11; i++)
      if (open[i] == str[count - 1]) flag = 1;
    int is_binary = 0;
    for (int i = 0; i < 6; i++)
      if (binary[i] == str[count - 1]) is_binary = 1;
    if (is_binary || flag || count == 0) {
      str[count] = "(";
      ui->result_show->setText(ui->result_show->text() + "(");
      count++;
      index_num = count;
      count_open++;
    } else
      ui->Error->setText("Сюда нельзя поставить открывающую скобку");
  } else if (count == 0) {
    str[count] = "(";
    ui->result_show->setText(ui->result_show->text() + "(");
    count++;
    index_num = count;
    count_open++;
  }
}

void MainWindow::un_function() {
  QPushButton *button = (QPushButton *)sender();
  ui->Error->setText("");
  // if (count == 0 && button->text() == "-")
  // {
  //     str[count] = button->text();
  //     QString num = "";
  //     for (int i = 0; i <= count; i++)
  //         num += str[i];
  //     ui->result_show->setText(num);
  //     count++;
  //     index_num = count;
  // }
  // else
  if (count == 1 && ui->pushButton_equal->isChecked()) {
    ui->pushButton_equal->setChecked(false);
    str[count] = button->text();
    QString num = "";
    for (int i = 0; i <= count; i++) num += str[i];
    ui->result_show->setText(num);
    count++;
    index_num = count;
  } else
  // if (count > 1)
  // {
  //     int flag = 0;
  //     for (int i = 0; i < 2; i++)
  //         if (unary[i] == str[count - 1])
  //             flag = 1;
  //     int is_digit = 0;
  //     for (int i = 0; i < 10; i++)
  //         if (digit[i] == str[count - 2])
  //             is_digit = 1;
  //     if (flag && (is_digit || str[count - 2] == ")" || str[count - 2] ==
  //     "x"))
  //     {
  //         str[count - 1] = button->text();
  //         QString num = "";
  //         for (int i = 0; i <= count - 1; i++)
  //             num += str[i];
  //         ui->result_show->setText(num);
  //     }
  //     else
  //     {
  //         int flag = 0;
  //         for (int i = 0; i < 10; i++)
  //             if (digit[i] == str[count - 1])
  //                 flag = 1;
  //         if (flag || str[count - 1] == "x" || str[count - 1] == ")")
  //         {
  //             str[count] = button->text();
  //             QString num = "";
  //             for (int i = 0; i <= count; i++)
  //                 num += str[i];
  //             ui->result_show->setText(num);
  //             count++;
  //             index_num = count;
  //         }
  //         else if (button->text() == "-")
  //         {
  //             int flag = 0;
  //             for (int i = 0; i < 11; i++)
  //                 if (open[i] == str[count - 1])
  //                     flag = 1;
  //             int is_binary = 0;
  //             for (int i = 0; i < 6; i++)
  //                 if (binary[i] == str[count - 1])
  //                     is_binary = 1;
  //             if (is_binary || flag)
  //             {
  //                 str[count] = button->text();
  //                 QString num = "";
  //                 for (int i = 0; i <= count; i++)
  //                     num += str[i];
  //                 ui->result_show->setText(num);
  //                 count++;
  //                 index_num = count;
  //             }
  //         }
  //     }
  // }
  // else if (count > 0)
  // {
  //     int flag = 0;
  //     for (int i = 0; i < 10; i++)
  //         if (digit[i] == str[count - 1])
  //             flag = 1;
  //     if (flag || str[count - 1] == "x" || str[count - 1] == ")")
  //     {
  //         str[count] = button->text();
  //         QString num = "";
  //         for (int i = 0; i <= count; i++)
  //             num += str[i];
  //         ui->result_show->setText(num);
  //         count++;
  //         index_num = count;
  //     }
  //     else if (button->text() == "-")
  //     {
  //         int flag = 0;
  //         for (int i = 0; i < 11; i++)
  //             if (open[i] == str[count - 1])
  //                 flag = 1;
  //         int is_binary = 0;
  //         for (int i = 0; i < 6; i++)
  //             if (binary[i] == str[count - 1])
  //                 is_binary = 1;
  //         if (is_binary || flag)
  //         {
  //             str[count] = button->text();
  //             QString num = "";
  //             for (int i = 0; i <= count; i++)
  //                 num += str[i];
  //             ui->result_show->setText(num);
  //             count++;
  //             index_num = count;
  //         }
  //     }
  // }
  {
    if (count == 0) {
      str[count] = button->text();
      QString num = "";
      for (int i = 0; i <= count; i++) num += str[i];
      ui->result_show->setText(num);
      count++;
      index_num = count;
    } else if (str[count - 1] == ".")
      ui->Error->setText("После \".\" нельзя ввести " + button->text());
    else if (count == 1 && isUnary(count - 1))
      ui->Error->setText("Здесь нельзя ввести " + button->text());
    else if (!isUnary(count - 1)) {
      str[count] = button->text();
      QString num = "";
      for (int i = 0; i <= count; i++) num += str[i];
      ui->result_show->setText(num);
      count++;
      index_num = count;
    } else if (count > 1) {
      if ((isDigit(count - 2) || str[count - 2] == ")" ||
           str[count - 2] == "x") &&
          (str[count - 1] == ")" || isBinary(count - 1))) {
        str[count] = button->text();
        QString num = "";
        for (int i = 0; i <= count; i++) num += str[i];
        ui->result_show->setText(num);
        count++;
        index_num = count;
      } else if (isDigit(count - 1) && isDigit2(count - 2)) {
        str[count] = button->text();
        QString num = "";
        for (int i = 0; i <= count; i++) num += str[i];
        ui->result_show->setText(num);
        count++;
        index_num = count;
      } else
        ui->Error->setText("Здесь нельзя ввести " + button->text());
    }
  }
}

int isUnary(int index) {
  int flag = 0;
  for (int i = 0; i < 2; i++)
    if (unary[i] == str[index]) flag = 1;
  return flag;
}

int isBinary(int index) {
  int flag = 0;
  for (int i = 0; i < 6; i++)
    if (binary[i] == str[index]) flag = 1;
  return flag;
}

int isDigit(int index) {
  int is_digit = 0;
  for (int i = 0; i < 10; i++)
    if (digit[i] == str[index]) is_digit = 1;
  return is_digit;
}

int isDigit2(int index) {
  int is_digit = 0;
  for (int i = 0; i < 11; i++)
    if (digit[i] == str[index]) is_digit = 1;
  return is_digit;
}

void MainWindow::bi_function() {
  QPushButton *button = (QPushButton *)sender();
  ui->Error->setText("");
  if (count != 0) {
    int flag = 0;
    for (int i = 0; i < 10; i++)
      if (digit[i] == str[count - 1]) flag = 1;
    if (count == 1 && ui->pushButton_equal->isChecked()) {
      ui->pushButton_equal->setChecked(false);
      str[count] = button->text();
      QString num = "";
      for (int i = 0; i <= count; i++) num += str[i];
      ui->result_show->setText(num);
      count++;
      index_num = count;
    } else if (flag || str[count - 1] == "x" || str[count - 1] == ")") {
      str[count] = button->text();
      QString num = "";
      for (int i = 0; i <= count; i++) num += str[i];
      ui->result_show->setText(num);
      count++;
      index_num = count;
    } else
      ui->Error->setText("Здесь нельзя ввести бинарную функцию " +
                         button->text());
  } else
    ui->Error->setText("Нельзя начинать с бинарной функции " + button->text());
}

void MainWindow::on_pushButton_equal_clicked() {
  ui->Error->setText("");
  QPushButton *button = (QPushButton *)sender();
  if (count_open != 0)
    ui->Error->setText("Не хватает " + QString::number(count_open, 'g', 10) +
                       " закрывающих скобок");
  else {
    QString num = ui->result_show->text();
    QByteArray ba = num.toLocal8Bit();
    char *func = ba.data();
    if (ui->xMin->text().toDouble() < -1000000.0 &&
        ui->xMax->text().toDouble() > 1000000.0)
      ui->Error->setText(
          "X min не может быть меньше -1000000 и X max не может быть больше "
          "1000000");
    else if (ui->xMin->text().toDouble() < -1000000.0)
      ui->Error->setText("X min не может быть меньше -1000000");
    else if (ui->xMax->text().toDouble() > 1000000.0)
      ui->Error->setText("X max не может быть больше 1000000");
    else {
      if (num.contains('x')) {
        ui->widget->clearGraphs();
        ui->widget->replot();
        QString string = ui->result_show->text();
        if (!string.isEmpty()) {
          h = 0.1;
          xBegin = ui->xMin->text().toDouble();
          xEnd = ui->xMax->text().toDouble();
          double y_min = 0;
          double y_max = 0;
          for (X = xBegin; X <= xEnd; X += h) {
            x.push_back(X);
            Y = calculate_is(func, X);
            if (Y < y_min && !(Y < -1000000.0)) {
              y_min = Y * 1.1;
            }
            if (Y > y_max && !(Y > 1000000.0)) {
              y_max = Y * 1.1;
            }
            y.push_back(Y);
          }
          if (xBegin < xEnd) {
            ui->widget->xAxis->setRange(xBegin, xEnd);
            ui->widget->yAxis->setRange(y_min, y_max);
          } else {
            ui->widget->xAxis->setRange(xEnd, xBegin);
            ui->widget->yAxis->setRange(y_min, y_max);
          }
          ui->widget->addGraph();
          ui->widget->graph(0)->addData(x, y);
          ui->widget->replot();
          x.clear();
          y.clear();
        }
      } else {
        CEXCEPTION_T e;
        Try {
          double j = 1.0;
          double result = calculate_is(func, j);
          ui->widget->clearGraphs();
          ui->widget->replot();
          QString string = ui->result_show->text();
          if (!string.isEmpty()) {
            h = 0.1;
            xBegin = ui->xMin->text().toDouble();
            xEnd = ui->xMax->text().toDouble();
            double y_min = 0;
            double y_max = 0;
            for (X = xBegin; X <= xEnd; X += h) {
              x.push_back(X);
              Y = calculate_is(func, X);
              if (Y < y_min && !(Y < -1000000.0)) {
                y_min = Y * 1.1;
              }
              if (Y > y_max && !(Y > 1000000.0)) {
                y_max = Y * 1.1;
              }
              y.push_back(Y);
            }
            if (xBegin < xEnd) {
              ui->widget->xAxis->setRange(xBegin, xEnd);
              ui->widget->yAxis->setRange(y_min, y_max);
            } else {
              ui->widget->xAxis->setRange(xEnd, xBegin);
              ui->widget->yAxis->setRange(y_min, y_max);
            }
            ui->widget->addGraph();
            ui->widget->graph(0)->addData(x, y);
            ui->widget->replot();
            x.clear();
            y.clear();
          }
          button->setChecked(true);
          string = "";
          if (result == round(result))
            string = QString::number(result, 'g', 10);
          else
            string = QString::number(result, 'd', 7);
          ui->result_show->setText(string);
          for (int i = 0; i <= count; i++) str[i] = "";
          count = 0;
          str[count] = ui->result_show->text();
          count++;
          index_num = count;
          count_open = 0;
        }
        Catch(e) {
          switch (e) {
            case 1:
              ui->Error->setText("Алё, ты делишь на 0, чувак...");
              ui->pushButton_equal->setChecked(false);
              break;
            case 2:
              ui->Error->setText("В ctg(...) присутствует деление на 0");
              ui->pushButton_equal->setChecked(false);
              break;
            case 3:
              ui->Error->setText("В acos(...) число < -1, либо > 1");
              ui->pushButton_equal->setChecked(false);
              break;
            case 4:
              ui->Error->setText("В asin(...) число < -1, либо > 1");
              ui->pushButton_equal->setChecked(false);
              break;
            case 5:
              ui->Error->setText("После mod 0");
              ui->pushButton_equal->setChecked(false);
              break;
            case 6:
              ui->Error->setText("Число слева от mod не целое =(");
              ui->pushButton_equal->setChecked(false);
              break;
            case 7:
              ui->Error->setText("Число справа от mod не целое =(");
              ui->pushButton_equal->setChecked(false);
              break;
            case 8:
              ui->Error->setText("Числа справа и слева от mod не целые =(");
              ui->pushButton_equal->setChecked(false);
              break;
            case 9:
              ui->Error->setText("Под корнем отрицательное число =(");
              ui->pushButton_equal->setChecked(false);
              break;
          }
        }
      }
    }
  }
}
