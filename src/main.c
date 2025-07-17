#include "Queue.h"
#include "Snake.h"
#include "Threads.h"


#include "DisplayFuncs.h"
#include "buttons.h"

void remove_maximize_button(HWND handle);

void idle() {
  glutPostRedisplay();
  Sleep(16);
}

void remove_maximize_button(HWND handle) {
  LONG style = GetWindowLong(handle, GWL_STYLE);
  style &= ~WS_MAXIMIZEBOX;
  style &= ~WS_THICKFRAME;
  SetWindowLong(handle, GWL_STYLE, style);
  SetWindowPos(handle, NULL, 0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  int x = 300;
  int y = 200;
  glutInitWindowPosition(x, y);
  int win = glutCreateWindow("CNake Game");
  remove_maximize_button(FindWindow(NULL, "CNake Game"));

  glDisable(GL_DEPTH_TEST);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutMouseFunc(start_button_click);
  glutSpecialFunc(arrow_handle);

  glutMainLoop();

  if (game_handle)
    CloseHandle(game_handle);
  return 1;
}

int main_biz_model() {
  DWORD threadMID;
  DWORD threadSDID;
  sTail = InitQueue();
  bool GameOver = false;
  sContent.mutex = CreateMutex(NULL, false, NULL);

  if (sContent.mutex == NULL) {
    fprintf(stdout, "Mutex creation failed: %d\n", GetLastError());
    return 1;
  }

  DataS data = {&sContent, &GameOver};
  FullData fdata = {&sContent, &GameOver, &sTail};
  InitSnake(&sContent);

  HANDLE hMovement = NewThread(&threadMID, MovementThread, &fdata);
  HANDLE hDirection = NewThread(&threadSDID, DirectionThread, &data);

  WaitForSingleObject(hMovement, INFINITE);
  WaitForSingleObject(hDirection, INFINITE);

  fprintf(stdout, "Game over!");
  CloseHandle(hMovement);
  CloseHandle(hDirection);
  FreeMap(&sContent);
  FreeQueue(&sTail);
  exit(0);
}