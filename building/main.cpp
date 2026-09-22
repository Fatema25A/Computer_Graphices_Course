#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
void box(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float xf, float yf)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1+xf,y1+yf);
    glVertex2f(x2+xf,y2+yf);
    glVertex2f(x3+xf,y3+yf);
    glVertex2f(x4+xf,y4+yf);
    glEnd();
}
void building()
{
    glColor3ub(255,0,0);
    box(2,28,16,28,16,0,2,0,0,0);
    glColor3ub(255,255,0);
    box(6,4,12,4,12,0,6,0,0,0);
    //left windows
    box(2.82,7.91,2.78,5.91,6,6,6,8,0,0);
    box(2.82,7.91,2.78,5.91,6,6,6,8,0,4);
    box(2.82,7.91,2.78,5.91,6,6,6,8,0,8);
    box(2.82,7.91,2.78,5.91,6,6,6,8,0,12);
    box(2.82,7.91,2.78,5.91,6,6,6,8,0,16);
    //right windows
    box(2.82,7.91,2.78,5.91,6,6,6,8,9,0);
    box(2.82,7.91,2.78,5.91,6,6,6,8,9,4);
    box(2.82,7.91,2.78,5.91,6,6,6,8,9,8);
    box(2.82,7.91,2.78,5.91,6,6,6,8,9,12);
    box(2.82,7.91,2.78,5.91,6,6,6,8,9,16);

}
/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
	building();

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("OpenGL Setup Test");
	//gluOrtho2D(-0.1,0.7,-0.1,0.3); // Create a window with the given title
	glutInitWindowSize(320, 320);// Set the window's initial width & height
	glutDisplayFunc(display);// Register display callback handler for window re-paint
	gluOrtho2D(-35,35,-35,35);
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}
