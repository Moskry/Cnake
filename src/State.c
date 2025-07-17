#include "State.h"

int width = 540;
int height = 700;
bool start_flag = false;
HANDLE game_handle;
DWORD main_id;
bool button_blocker = false;
bool init_map = false;

// from legacy main logic
IntTuple pos;
SharedContent sContent = {20, 20, 'W', &pos, 0};
Queue *sTail;