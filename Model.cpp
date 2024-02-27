#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "readInputFile.h"
#include "Model.h"
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <loadpng.h>
#include <process_image.h>
#include <gl_texture.h>

using namespace std;



void Model::load_MTL(const char* filename) {
    string line;
    vector<string> lines;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Can't load file " << filename << endl;
        return;
    }

    while (!file.eof()) {
        getline(file, line);
        lines.push_back(line);
    }
    file.close();

    int count = 0;
    string tmp;
    string material;
    float* a, * d, * s;
    Material* m = new Material(NULL, NULL, NULL);

    for (string& line : lines) {
        if (line[0] == 'n' && line[1] == 'e') {
            readMaterialName(line, tmp);
            material = tmp;
            map_material[material] = count++;
            a = new float[4] {0.2f, 0.2f, 0.2f, 1.0f};
            d = new float[4] {0.8f, 0.8f, 0.8f, 1.0f};
            s = new float[4] {0.0f, 0.0f, 0.0f, 1.0f};
            materials.push_back(Material(a, d, s));
            m = &materials.back();
        }
        else if (line[0] == 'K') {
            readK(line, a, d, s);
        }
        else if (line[0] == 'm' && line[1] == 'a') {
            readMap_Kd(line, tmp);
            string file = directory + tmp;
            cout << "===========" << file << endl;
            Image img;
            Load_Texture_Swap(&img, file.c_str());
            glGenTextures(1, &(m->texture));
            glBindTexture(GL_TEXTURE_2D, m->texture);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.img);
            glBindTexture(GL_TEXTURE_2D, 0);
            Delete_Image(&img);
        }
    }
}

void Model::load_model(const char* filename) {
    string temp = filename;
    directory = "";
    int index = 0;
    for (int i = temp.size() - 1; i > 0; i--) {
        if (temp[i] == '/') {
            index = i + 1;
            break;
        }
    }
    for (int i = 0; i < index; i++)
        directory += temp[i];

    string line;
    vector<string> lines;
    ifstream file(filename);
    file.is_open();
    while (!file.eof()) {
        getline(file, line);
        lines.push_back(line);
    }
    file.close();

    string str;
    string faceName;

    pos_x = pos_y = 0.0f;
    float sum_x = 0.0f, sum_y = 0.0f, sum_z = 0.0f;

    for (string& line : lines) {
        if (line[0] == 'v') {
            if (line[1] == ' ') {
                readV(line, a, b, c);
                sum_x += abs(a);
                sum_y += abs(b);
                sum_z += abs(c);
                pos_x += a;
                pos_y += b;
                vertices.push_back(new float[3] {a, b, c});
            }
            else if (line[1] == 't') {
                readVT(line, a, b);
                texcoords.push_back(new float[2] {a, b});
            }
            else {
                readVN(line, a, b, c);
                normals.push_back(new float[3] {a, b, c});
            }
        }
        else if (line[0] == 'f') {
            readF(line, v, t, n, num);
            int* vv = new int[num];
            int* tt = new int[num];

            for (int i = 0; i < num; i++) {
                vv[i] = v[i] - 1;
                tt[i] = t[i] - 1;
            }

            faces.push_back(Face(num, vv, tt, n - 1));
        }
        else if (line[0] == 'm' && line[1] == 't') {
            readMTL(line, str);
            string file = directory + str;
            load_MTL(file.c_str());
        }
        else if (line[0] == 'u' && line[1] == 's') {
            readUsemtl(line, str);
            string material = str;
            if (map_material.find(material) != map_material.end())
                faces.push_back(Face(-1, NULL, NULL, map_material[material]));
        }
    }

    bool has_texcoord = false;
    list = glGenLists(1);

    glNewList(list, GL_COMPILE);
    for (Face& face : faces) {

        if (face.edge == -1) {
            has_texcoord = false;
            glLightfv(GL_LIGHT0, GL_AMBIENT, materials[face.normal].ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, materials[face.normal].diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, materials[face.normal].specular);
            if (materials[face.normal].texture != 0) {
                has_texcoord = true;
                glBindTexture(GL_TEXTURE_2D, materials[face.normal].texture);
            }
            continue;
        }
        if (face.normal != -1)
            glNormal3fv(normals[face.normal]);
        else
            glDisable(GL_LIGHTING);
        if (has_texcoord) {
            glBegin(GL_POLYGON);
            for (int i = 0; i < face.edge; i++) {
                glTexCoord2fv(texcoords[face.texcoords[i]]);
                glVertex3fv(vertices[face.vertices[i]]);
            }
            glEnd();
        }
        else {
            glBegin(GL_POLYGON);
            for (int i = 0; i < face.edge; i++)
            {
                glVertex3fv(vertices[face.vertices[i]]);
            }
            glEnd();
        }
        if (face.normal == -1)
            glEnable(GL_LIGHTING);
    }
    glEndList();

    //cout << "Model: " << filename << endl;
    //cout << "Vertices: " << vertices.size() << endl;
    //cout << "Texcoords: " << texcoords.size() << endl;
    //cout << "Normals: " << normals.size() << endl;
    //cout << "Faces: " << faces.size() << endl;
    //cout << "Materials: " << materials.size() << endl;

    sum_x /= vertices.size();
    sum_y /= vertices.size();
    sum_z /= vertices.size();
    pos_x /= vertices.size();
    pos_x = -pos_x;
    pos_y /= vertices.size();
    pos_y = -pos_y;
    pos_z = -sqrt(sum_x * sum_x + sum_y * sum_y + sum_z * sum_z) * 15;

    //cout << "PosX: " << pos_x << endl;
    //cout << "PosY: " << pos_y << endl;
    //cout << "PosZ: " << pos_z << endl;

    materials.clear();
    map_material.clear();
    for (float* f : vertices)
        delete f;
    vertices.clear();
    for (float* f : texcoords)
        delete f;
    texcoords.clear();
    for (float* f : normals)
        delete f;
    normals.clear();
    faces.clear();
}

void Model::draw() {
    glCallList(list);
}
