
#include "text.h"

#include <GL/gl.h>
#include <stdio.h>

//funkce pro kresleni jednotlivych znaku (charu)
void draw_char(char c) {
	glBegin(GL_LINES);
	switch (c) {
		case '0': 
			glVertex2f(2, 1);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(2, 1);
			glVertex2f(2, 3);
			glVertex2f(3, 4);
			break;
		case '1':	
			glVertex2f(3, 1);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(1, 4);
			break;
		case '2':
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 4);
			glVertex2f(4, 4);
			glVertex2f(1, 1);
			glVertex2f(1, 1);
			glVertex2f(4, 1);
			break;
		case '3':
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 4);
			glVertex2f(4, 4);
			glVertex2f(3, 3.5);
			glVertex2f(3, 3.5);
			glVertex2f(4, 3);
			glVertex2f(4, 3);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			break;
		case '4':
			glVertex2f(3, 1);
			glVertex2f(3, 5);
			glVertex2f(4, 3);
			glVertex2f(1, 3);
			glVertex2f(1, 3);
			glVertex2f(1, 6);
			break;	
		case '5':
			glVertex2f(1, 2);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(4, 3);
			glVertex2f(4, 3);
			glVertex2f(3, 4);
			glVertex2f(3, 4);
			glVertex2f(1, 4);
			glVertex2f(1, 4);
			glVertex2f(1, 6);
			glVertex2f(1, 6);
			glVertex2f(4, 6);
			break;
		case '6':
			glVertex2f(4, 5);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(4, 3);
			glVertex2f(4, 3);
			glVertex2f(3, 4);
			glVertex2f(3, 4);
			glVertex2f(2, 4);
			glVertex2f(2, 4);
			glVertex2f(1, 3);
			break;
		case '7':
			glVertex2f(2, 1);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 6);
			glVertex2f(4, 6);
			glVertex2f(1, 6);
			break;
		case '8':
			glVertex2f(2, 3.5);
			glVertex2f(1, 3);
			glVertex2f(1, 3);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(4, 3);
			glVertex2f(4, 3);
			glVertex2f(3, 3.5);
			glVertex2f(3, 3.5);
			glVertex2f(2, 3.5);
			glVertex2f(2, 3.5);
			glVertex2f(1, 4);
			glVertex2f(1, 4);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 4);
			glVertex2f(4, 4);
			glVertex2f(3, 3.5);
			break;
		case '9':
			glVertex2f(1, 2);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(1, 4);
			glVertex2f(1, 4);
			glVertex2f(2, 3);
			glVertex2f(2, 3);
			glVertex2f(3, 3);
			glVertex2f(3, 3);
			glVertex2f(4, 4);
			break;
		case 'A':
			glVertex2f(1, 1);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 1);
			glVertex2f(1, 3.5);
			glVertex2f(4, 3.5);
			break;
		case 'C':
			glVertex2f(4, 2);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			break;
		case 'E':
			glVertex2f(4, 1);
			glVertex2f(1, 1);
			glVertex2f(1, 1);
			glVertex2f(1, 6);
			glVertex2f(1, 6);
			glVertex2f(4, 6);
			glVertex2f(1, 3.5);
			glVertex2f(3, 3.5);
			break;
		case 'F':
			glVertex2f(1, 1);
			glVertex2f(1, 6);
			glVertex2f(1, 6);
			glVertex2f(4, 6);
			glVertex2f(1, 3.5);
			glVertex2f(3, 3.5);
			break;
		case 'G':
			glVertex2f(2, 3);
			glVertex2f(4, 3);
			glVertex2f(4, 3);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			break;
		case 'I':
			glVertex2f(2, 1);
			glVertex2f(3, 1);
			glVertex2f(2.5, 1);
			glVertex2f(2.5, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			break;
		case 'L':
			glVertex2f(1, 6);
			glVertex2f(1, 1);
			glVertex2f(1, 1);
			glVertex2f(4, 1);
			break;
		case 'M':
			glVertex2f(1, 1);
			glVertex2f(1, 6);
			glVertex2f(1, 6);
			glVertex2f(2.5, 4);
			glVertex2f(2.5, 4);
			glVertex2f(4, 6);
			glVertex2f(4, 6);
			glVertex2f(4, 1);
			break;
		case 'O':
			glVertex2f(2, 1);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(2, 1);
			break;
		case 'P':
			glVertex2f(1, 1);
			glVertex2f(1, 6);
			glVertex2f(1, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 4);
			glVertex2f(4, 4);
			glVertex2f(3, 3);
			glVertex2f(3, 3);
			glVertex2f(1, 3);
			break;
		case 'R':
			glVertex2f(1, 1);
			glVertex2f(1, 6);
			glVertex2f(1, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			glVertex2f(4, 5);
			glVertex2f(4, 4);
			glVertex2f(4, 4);
			glVertex2f(3, 3);
			glVertex2f(3, 3);
			glVertex2f(1, 3);
			glVertex2f(2.5, 3);
			glVertex2f(4, 1);
			break;
		case 'S':
			glVertex2f(1, 2);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(4, 3);
			glVertex2f(4, 3);
			glVertex2f(3, 3.5);
			glVertex2f(3, 3.5);
			glVertex2f(2, 3.5);
			glVertex2f(2, 3.5);
			glVertex2f(1, 4);
			glVertex2f(1, 4);
			glVertex2f(1, 5);
			glVertex2f(1, 5);
			glVertex2f(2, 6);
			glVertex2f(2, 6);
			glVertex2f(3, 6);
			glVertex2f(3, 6);
			glVertex2f(4, 5);
			break;
		case 'T':
			glVertex2f(1, 6);
			glVertex2f(4, 6);
			glVertex2f(2.5, 1);
			glVertex2f(2.5, 6);
			break;
		case 'U':
			glVertex2f(1, 6);
			glVertex2f(1, 2);
			glVertex2f(1, 2);
			glVertex2f(2, 1);
			glVertex2f(2, 1);
			glVertex2f(3, 1);
			glVertex2f(3, 1);
			glVertex2f(4, 2);
			glVertex2f(4, 2);
			glVertex2f(4, 6);
			break;
		case 'V':
			glVertex2f(1, 6);
			glVertex2f(1, 4);
			glVertex2f(1, 4);
			glVertex2f(2.5, 1);
			glVertex2f(2.5, 1);
			glVertex2f(4, 4);
			glVertex2f(4, 4);
			glVertex2f(4, 6);
			glVertex2f(4, 6);
			break;
		case 'W':
			glVertex2f(1, 6);
			glVertex2f(1.5, 1);
			glVertex2f(1.5, 1);
			glVertex2f(2.5, 4);
			glVertex2f(2.5, 4);
			glVertex2f(3.5, 1);
			glVertex2f(3.5, 1);
			glVertex2f(4, 6);
			break;
		case 'Y':
			glVertex2f(2.5, 1);
			glVertex2f(2.5, 4);
			glVertex2f(2.5, 4);
			glVertex2f(4, 6);
			glVertex2f(2.5, 4);
			glVertex2f(1, 6);
			break;
		case ' ':
			break;
		default: 
			glVertex2f(0, 0);
			glVertex2f(5, 7);
			glVertex2f(5, 0);
			glVertex2f(0, 7);
			break;
	}
	glEnd();
}

//kresli text do hry
void draw_string(char* s) {
	glPushMatrix();

	//scale pro dobrou praci s chary
	glScalef(0.125, 0.125, 1);

	for(;*s;s++) { //s++: adresa++
		draw_char(*s);
		glTranslatef(5, 0, 0);
	}
	glPopMatrix();
}

//predelava cisla na chary
void draw_int(int n) {
	char buffer[64];
	sprintf(buffer, "%d", n);
	draw_string(buffer);
}

