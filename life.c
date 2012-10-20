#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RETURN 13
#define ESCAPE 27
#define SPACE  32
#define P      112

int window;
int size = 1000;
int current[1000][1000];
int next[1000][1000];

void initBoard(int *board, int n) {
  int i, j;
  for(i=0; i < n; i++)
    for(j = 0; j < n; j++)
      board[i*n + j] = 0;
}

void randomize(int *board, int n) {
  int i, j;
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      board[n*i + j] = random() % 2;
}

void getNext(int *board, int *next, int n) {
  int i, j;
  int count;
  for(i = 1; i < n-1; i++) {
    for(j = 1; j < n-1; j++) {
      count = 0;
      if(board[n*(i-1)+j])
        count++;
      if(board[n*(i-1)+(j-1)])
        count++;
      if(board[n*(i-1)+(j+1)])
        count++;
      if(board[n*i + (j-1)])
        count++;
      if(board[n*i + (j+1)])
        count++;
      if(board[n*(i+1) + (j-1)])
        count++;
      if(board[n*(i+1) + j])
        count++;
      if(board[n*(i+1) + (j+1)])
        count++;
      if(board[n*i + j]) {
        if(count < 2 || count > 3)
          next[n*i + j] = 0;
        else
          next[n*i + j] = 1;
      } else {
        if(count == 3)
          next[n*i + j] = 1;
        else
          next[n*i + j] = 0;
      }
    }
  }
  memcpy(board, next, sizeof(int) * n * n);
}

void initGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
}

void resizeGL(int w, int h) {
  if(h == 0) { h=1; }
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat)w/h, 0.1f, 200.0f);
  glMatrixMode(GL_MODELVIEW);
}

float randomf() {
  float mmm = 2147483647;
  return rand()/mmm;
}

void drawBoard() {
  int i, j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(-40.0, -40.0, -50.0);
  glPushMatrix();
  glPointSize(3.0f);
  glBegin(GL_POINTS);
  for(i=0; i < size; i++) {
    for(j=0; j < size; j++) {
      if(current[i][j]) {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      }
      else {
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
      }
      glVertex3f(i*(0.5f), j*(0.5f), -6.0f);
    }
  }
  glEnd();
  glPopMatrix();
  glutSwapBuffers();
}

void update() {
  getNext(*current, *next, size);
  drawBoard();
}

void keyPressed(unsigned char key, int x, int y) {
  usleep(100);
  if(key == ESCAPE) {
    glutDestroyWindow(window);
    exit(0);
  }
  if(key == SPACE)
    randomize(*current, size);
  if(key == RETURN)
    getNext(*current, *next, size);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(800, 600);

  window = glutCreateWindow("life");

  initBoard(*current, size);
  randomize(*current, size);

  glutDisplayFunc(&drawBoard);
  glutIdleFunc(&update);
  glutReshapeFunc(&resizeGL);
  glutKeyboardFunc(&keyPressed);

  initGL();
  glutMainLoop();
  return 1;
}
