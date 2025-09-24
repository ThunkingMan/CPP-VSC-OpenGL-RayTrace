#include "RenderClass.h"
#include "glm\glm.hpp"


struct VertexPosTex {
    glm::vec3 Pos;
    glm::vec2 Tex;
    VertexPosTex() {Pos=glm::vec3(0.0f, 0.0f, 0.0f); Tex = glm::vec2(0.0f, 0.0f);}
    VertexPosTex(glm::vec3 _Pos, glm::vec2 _Tex) {Pos = _Pos; Tex = _Tex;}
};


RenderClass::RenderClass() {}
RenderClass::RenderClass(const RenderClass&) {}
RenderClass::~RenderClass() {}

void RenderClass::Init() {

}

void RenderClass::CreateDisplaySqr() {
    //Create square for display of raytrace texture
    
    VertexPosTex Vertex[4] = {
        VertexPosTex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)), //vert - top left
        VertexPosTex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)), //vert2 - bottom left
        VertexPosTex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)), //vert3 - Bottom right
        VertexPosTex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)) //vert4 - top right
    };
    GLuint Index[] = {0, 1, 2, 2, 3, 0}; //Index data

    glGenVertexArrays(1, &m_VAO); //Create VAO
    glGenBuffers(1, &m_VBO); //Create VBO
    glGenBuffers(1, &m_EBO); //Cretae EBO
    glBindVertexArray(m_VAO); //Bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); //BIND VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW); //Upload vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0); //Attribute 0 Vertex Position
    glEnableVertexAttribArray(0); //enable array atribute 0
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float))); //Attribute 1 texture position
    glEnableVertexAttribArray(1); //enable array atribute 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); //bind index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index), Index, GL_STATIC_DRAW); //Upload index data
    glBindVertexArray(0); //Unbind VAO;
}

void RenderClass::Render() {

}




