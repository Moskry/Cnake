#include "DisplayFuncs.h"

void draw_map(void) {
    if (!start_flag || !init_map) return;

    for (int i = 0; i < sContent.Height; i++) {
        for (int j = 0; j < sContent.Width * 2; j++) {
            char tile = sContent.Map[i][j];

            switch (tile) {
                case '@': 
                    glColor4f(0.5f, 0.5f, 0.0f, 1.0f); 
                    break;
                case 'O':
                    glColor4f(0.0f, 0.8f, 0.0f, 1.0f);
                    break;
                case '+':
                    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                    break;
                default:
                    continue;
            }
            draw_square(&sContent,j, i);
        }
    }
}