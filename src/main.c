#include "Snake.h"
#include "Threads.h"
#include "Queue.h"

#include "DisplayFuncs.h"
#include "buttons.h"

int width = 540;
int height = 700;
bool triangle_flag = false;

void remove_maximize_button(HWND handle);
int main_biz_model(SharedContent* Shared, Queue** Tail, HANDLE* hMovement, HANDLE* hDirection, DWORD* threadMID, DWORD* threadSDID);


void remove_maximize_button(HWND handle)
{
    LONG style = GetWindowLong(handle, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_THICKFRAME;
    SetWindowLong(handle, GWL_STYLE, style);
    SetWindowPos(handle, NULL, 0,0,0,0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

int main(int argc, char** argv)
{
    IntTuple pos;
    DWORD threadMID;
    DWORD threadSDID;

    HANDLE hMovement;
    HANDLE hDirection;

    SharedContent Shared = {20, 20, 'W', &pos, 0};
    Queue* Tail;

    int err = main_biz_model(&Shared, &Tail, &hMovement, &hDirection, &threadMID, &threadSDID);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    int x = 300;
    int y = 200;
    glutInitWindowPosition(x,y);
    int win = glutCreateWindow("Orthogonal Projection Example");
    remove_maximize_button(FindWindow(NULL, "Orthogonal Projection Example"));
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(start_button_click);

    glutMainLoop();

    fprintf(stdout, "Game over!");
    CloseHandle(hMovement);
    CloseHandle(hDirection);
    FreeMap(&Shared);
    FreeQueue(&Tail);
    
    return err;
}

int main_biz_model(SharedContent* Shared, Queue** Tail, HANDLE* hMovement, HANDLE* hDirection, DWORD* threadMID, DWORD* threadSDID)
{
    Queue* Tail = InitQueue();
    bool GameOver = false;
    Shared->mutex = CreateMutex(NULL, false, NULL);

    if (Shared->mutex == NULL) 
    {
        fprintf(stdout, "Mutex creation failed: %d\n", GetLastError());
        return 1;
    }
    
    DataS data = {Shared,&GameOver};
    FullData fdata = {Shared, &GameOver, &Tail};
    InitSnake(&Shared);
    
    *hMovement = NewThread(threadMID, MovementThread, &fdata);
    *hDirection = NewThread(threadSDID, DirectionThread, &data);

     //WaitForSingleObject(hMovement, INFINITE);
     //WaitForSingleObject(hDirection, INFINITE);

    //fprintf(stdout, "Game over!");
    return 1;
}
