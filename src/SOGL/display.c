#include "Queue.h"
#include "Snake.h"
#include "Threads.h"


#include "DisplayFuncs.h"
#include "buttons.h"

void display(void) {
  glClearColor(0.5, 0.5, 0.8, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // Draw in orthogonal mode
  orthogonalStart();
  glColor4f(0.8, 0.8, 0.8, 1.0);
  glBegin(GL_QUADS);
  glVertex2f(20, 20);
  glVertex2f(20, 520);
  glVertex2f(520, 520);
  glVertex2f(520, 20);
  glEnd();

  start_button();
  if (start_flag == true && button_blocker == false) {
    button_blocker = true;
    game_handle = NewThread(&main_id, MainThread, NULL);
  }

  // if (start_flag == true){
  //    glColor4f(0.0,0.8,0.0,1.0);
  //    draw_square();
  //}

  draw_map();

  orthogonalEnd();

  glutSwapBuffers();
  // fprintf(stdout,"%d\n%d",sContent.pos->x,sContent.pos->y);
  // fflush(stdout);
  glutPostRedisplay();
}
