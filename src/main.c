#include "Snake.h"
#include "Threads.h"
#include "Queue.h"

#include "DisplayFuncs.h"
#include "buttons.h"

int width = 540;
int height = 700;
bool start_flag = false;
HANDLE game_handle;
DWORD main_id;

void remove_maximize_button(HWND handle);


void remove_maximize_button(HWND handle)
{
    LONG style = GetWindowLong(handle, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_THICKFRAME;
    SetWindowLong(handle, GWL_STYLE, style);
    SetWindowPos(handle, NULL, 0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

int main(int argc, char** argv)
{
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
    
    CloseHandle(game_handle);
    return 1;
}

int main_biz_model()
{
    IntTuple pos;
    DWORD threadMID;
    DWORD threadSDID;
    SharedContent Shared = {20, 20, 'W', &pos, 0};
    Queue* Tail = InitQueue();
    bool GameOver = false;
    Shared.mutex = CreateMutex(NULL, false, NULL);

    if (Shared.mutex == NULL) 
    {
        fprintf(stdout, "Mutex creation failed: %d\n", GetLastError());
        return 1;
    }
    
    DataS data = {&Shared,&GameOver};
    FullData fdata = {&Shared, &GameOver, &Tail};
    InitSnake(&Shared);
    
    HANDLE hMovement = NewThread(&threadMID, MovementThread, &fdata);
    HANDLE hDirection = NewThread(&threadSDID, DirectionThread, &data);

     WaitForSingleObject(hMovement, INFINITE);
     WaitForSingleObject(hDirection, INFINITE);

    fprintf(stdout, "Game over!");
    CloseHandle(hMovement);
    CloseHandle(hDirection);
    FreeMap(&Shared);
    FreeQueue(&Tail);
    return 1;
}