#ifndef MATERIAL_H
#define MATERIAL_H
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
class Material {
public:
    float* ambient;
    float* diffuse;
    float* specular;
    GLuint texture;

    Material(float* ambient, float* diffuse, float* specular) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->texture = 0;
    }
};
#endif