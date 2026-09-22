#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cmath>
using namespace std;

GLuint sceneTexture;
GLuint loadTexture(const char* filename, int* outWidth = NULL, int* outHeight = NULL) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (!image) {
        printf("Failed to load image: %s\n", filename);
        return 0;
    }

    if (outWidth) *outWidth = width;
    if (outHeight) *outHeight = height;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(image);
    return textureID;
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Draw background
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.5f);
    glEnd();

    glutSwapBuffers();
}
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sceneTexture = loadTexture("truck.png");
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tank Animation with Flames on Buildings");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
