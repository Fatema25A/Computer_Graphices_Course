#include<windows.h>
#include<iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <cmath>
#include<cstdio>
#include "glutil.h"

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void background(){
glColor3d(1.0,1.0,1.0);
glBegin(GL_QUADS);            // These vertices form a closed polygon

	glVertex2f(0,1000);
	glVertex2f(0,400);
	glVertex2f(1900,400);
	glVertex2f(1900,1000);

	glEnd();
	ApplyTexture(0,400,1900,400,1900,1000,0,1000,textures[0].textureID);


}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
  // Clear the color buffer with current clearing color

background();

glutSwapBuffers();

	  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);          // Initialize GLUT
	 // Create window with the given title
	 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	//glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	//glutFullScreen();
	glutCreateWindow("PROJECT");
	loadImageAndStore("E:/SEM 8/COMPUTER GRAPHICS/third.bmp");
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
     glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0, 1900, 0, 1000);
	                  // Our own OpenGL initialization

	glMatrixMode(GL_MODELVIEW);  // Switch back for rendering
glLoadIdentity();
	glutMainLoop();                 // Enter the event-processing loop
	return 0;

}
