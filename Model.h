#ifndef MODEL_H
#define MODEL_H
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>
#include <glfw/glfw3.h>
using namespace std;
class Model
{
private:
    class Material {
    public:
        float* ambient;
        float* diffuse;
        float* specular;
        GLuint texture;

        Material(float* a, float* d, float* s) {
            this->ambient = a;
            this->diffuse = d;
            this->specular = s;
            this->texture = 0;
        }
    };
    class Face {
    public:
        int edge;
        int* vertices;
        int* texcoords;
        int normal;

        Face(int e, int* v, int* t, int n = -1) {
            this->edge = e;
            this->vertices = v;
            this->texcoords = t;
            this->normal = n;
        }
    };
    string directory;
    vector<Material> materials;
    map<string, int> map_material;
    vector<float*> vertices;
    vector<float*> texcoords;
    vector<float*> normals;
    vector<Face> faces;
    GLuint list;
    void load_MTL(const char* filename);

public:
    float a, b, c;
    int v[8], t[8], n;
    int num = 0;
    float pos_x, pos_y, pos_z;
    void load_model(const char* filename);
    void draw();
};
#endif