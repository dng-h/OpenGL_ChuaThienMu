#ifndef FACE_H
#define FACE_H

#include <GL/glew.h>
#include <glfw/glfw3.h>
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
using namespace std;
class Face {
public:
    int edge;
    int* vertices;
    int* texcoords;
    int normal;

    Face(int edge, int* vertices, int* texcoords, int normal = -1) {
        this->edge = edge;
        this->vertices = vertices;
        this->texcoords = texcoords;
        this->normal = normal;
    }
};
#endif