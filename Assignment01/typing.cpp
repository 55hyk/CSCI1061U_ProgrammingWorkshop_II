#include <iostream>
#include <curses.h>
#include <unistd.h> /*  for sleep()  */
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

const int MAX = 10;
int row[MAX], col[MAX];

// for generating random alphabets
void randAlphGen(char alph[], int i);

// reassign a random alphabet, row position and column position
void resetAlph(char alph[], int row[], int col[], const int MAX_WIDTH, int i);

int main() {
  int ch, h, w, score=0, missed=0;
  bool changeCol = true, changeAlph = true, miss = false;
  char alph[MAX];

  // initialize screen
  WINDOW* win = initscr();
  cbreak();
  curs_set(0);
  nodelay(stdscr, TRUE);
  noecho();
  keypad(stdscr, TRUE);

  srand(time(NULL));
  getmaxyx(stdscr, h, w);
  for (int i = 0; i < MAX; i++) { // fill up with random alphabet and column
    do { // the random alphabets that are all different
      randAlphGen(alph, i);
      changeAlph = false;
      for (int j = 0; j < i; j++) {
        if (alph[i] == alph[j]) {
          changeAlph = true;
        }
      }
    } while (changeAlph);
    row[i] = 0; // all start at the top
    do { // randomize the coordinates of the alphabets without overlaping
      col[i] = rand()%w;
      changeCol = false;
      for (int j = 0; j < i; j++) {
        if (col[i] == col[j]) {
          changeCol = true;
        }
      }
    } while (changeCol);
  }

  do { // game begins
    ch = getch();
    // to cast string into char* to output the status
    stringstream ss;
    string str, status;
    ss << score;
    ss >> str;
    status = "Current score is " + str + ". Enter ESC to exit.";
    const char* s = status.c_str();
    mvaddstr(h-1, 0, s);
    refresh();

    for (int i = 0; i < MAX; i++) { // loop over the alphabets
      if (ch == 27) { // if ESC is pressed, delete window and exit the loop
        delwin(win);
        endwin();
        refresh();
        break;
      }

      if (row[i] == (h-1)) { // if an alphabet reaches the bottom
        mvaddch(row[i]-1, col[i], ' ');
        for (int j = 0; j < MAX; j++) {
          if (ch == alph[j]) {         // if the alphabet is pressed, score 1
            mvaddch(row[j]-1, col[j], ' '); // and change the alphabet to '*'
            alph[j] = '*';
            score += 1;
          } else {
            miss = true;
          }
        }
        if (miss) { // if the alphabet is missed, missed + 1
          missed += 1;     // and assign another alphabet
          resetAlph(alph, row, col, w, i);
        }
      }

      if (alph[i] == '*') {     // if any positions holds an '*',
        mvaddch(row[i], col[i], ' '); // assign an alphabet to it
        resetAlph(alph, row, col, w, i);
      }

      // for the effect of letter descending from the top
      mvaddch(row[i]-1, col[i], ' ');
      mvaddch(row[i], col[i], alph[i]);
      row[i]++;

      //if the alphabet is pressed, change it to an '*' and score 1
      for (int j = 0; j < MAX; j++) {
        if (ch == alph[i]) {
          mvaddch(row[i]-1, col[i], '*');
          alph[i] = '*';
          score += 1;
        }
      }
    }

    refresh();
    usleep(200000); // delay between each frame

    // for the asterisks and the effect of showing the asterisks
    // when an alphabet is pressed
    for (int i = 0; i < MAX; i++) {
      if (alph[i] == '*') {
        mvaddch(row[i]-1, col[i], ' ');
        mvaddch(row[i], col[i], ' ');
      }
    }
    refresh();
  } while (ch != 27); // exit when pressing Esc

  // output the result
  cout << "Total score: " << score << endl
       << "Total missed: " << missed << endl;

  return 0;
}

void randAlphGen(char alph[], int i) {
  if (rand()%2 == 0) {
    alph[i] = (char)('A'+ rand()%26);
  } else {
    alph[i] = (char)('a'+ rand()%26);
  }
}

void resetAlph(char alph[], int row[], int col[], const int MAX_WIDTH, int i) {
  randAlphGen(alph, i);
  row[i] = 0;
  col[i] = rand()%MAX_WIDTH;
  for (int k = 0; k < MAX; k++) {
    if ((row[i] == row[k]) && (i != k)) {
      if (col[i] == col[k]) {
        randAlphGen(alph, i);
      }
    }
  }
}
