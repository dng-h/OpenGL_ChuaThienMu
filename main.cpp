#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include "Model.h"
#include <GL/glew.h>
#include <glfw/glfw3.h>
using namespace std;

const GLuint WIDTH = 1920, HEIGHT = 1080;
const char* TITLE = "Chua Thien Mu";

string model_name = "ChuaThienMuFinal.obj";

GLfloat light_pos[] = { -1000.0f, 1000.0f, 0.0f, 1.0f };
float posX, posY, posZ;
float angleX = 0.0f, angleY = 0.0f;
float angle_light = 0.0;

int x_old = 0, y_old = 0;
float zoom;
bool mouse_holding = false;
bool updating_model = false;

void key(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_Z) {
        if(action == GLFW_PRESS)
            posZ += zoom;
    }
    if (key == GLFW_KEY_X) {
        if(action == GLFW_PRESS)
            posZ -= zoom;
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        posY -= 3;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        posY += 3;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        posX += 3;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        posX -= 3;
    }
}

void mouse(GLFWwindow* window, int key, int action, int mode)
{
    updating_model = true;
    if (key == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double x_pos, y_pos;
            glfwGetCursorPos(window, &x_pos, &y_pos);
            x_old = x_pos;
            y_old = y_pos;
            mouse_holding = true;
        }
        else mouse_holding = false;
    }
}

void motion(GLFWwindow* window, double x, double y) {
    if (mouse_holding) {
        updating_model = true;
        angleY += (x - x_old) / 5;
        x_old = x;
        if (angleY > 360.0f)
            angleY -= 360.0f;
        else if (angleY < 0.0f)
            angleY += 360.0f;

        angleX += (y - y_old) / 5;
        y_old = y;
        if (angleX > 360.0f)
            angleX -= 360.0f;
        else if (angleX < 0.0f)
            angleX += 360.0f;

    }
}
Model model;

int main(void)
{
    glfwInit();
	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	GLenum glewInitResult = glewInit();

	// Set the viewport size
	glViewport(0, 0, WIDTH, HEIGHT);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    gluPerspective(20.0, 1.0, 1.0, 2000.0);

	glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    model.load_model(model_name.c_str());

    posX = model.pos_x;
    posY = model.pos_y;
    posZ = model.pos_z - 1.0;

    zoom = -model.pos_z / 50.0;


	// Set the GLFW key callback function
	glfwSetKeyCallback(window, key);
    glfwSetMouseButtonCallback(window, mouse);
    glfwSetCursorPosCallback(window, motion);

	glfwMakeContextCurrent(window);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(posX, posY, posZ/10);
        glRotatef(angleX, 1.0f, 0.0f, 0.0f);
        glRotatef(angleY, 0.0f, 1.0f, 0.0f);

        glPushMatrix();
        if (angle_light > 360.0)
            angle_light -= 360;
        else
            angle_light += 1.0;
        glRotatef(angle_light, 0.0f, 0.0f, 1.0f);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glPopMatrix();

        model.draw();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();

	return 0;

}


