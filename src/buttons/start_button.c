#include "buttons.h"

int start_button_x = 20; 
int start_button_y = 540;
int start_button_width = 100;
int start_button_height = 60;

void start_button(void)
{
    glColor4f(0.3,0.3,0.3,1.0); // Counter clock-wise
    glBegin(GL_QUADS);
    glVertex2f(start_button_x, start_button_y);
    glVertex2f(start_button_x,start_button_height + start_button_y);
    glVertex2f(start_button_x + start_button_width, start_button_height + start_button_y);
    glVertex2f(start_button_x + start_button_width, start_button_y);
    glEnd();
}

void start_button_click(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //int flippedY = height - y;

        if (x >= start_button_x && x <= start_button_x + start_button_width &&
            y >= start_button_y && y <= start_button_y + start_button_height){
                //glutDisplayFunc(draw_triangle);
                start_flag = true;
            }
    }
}