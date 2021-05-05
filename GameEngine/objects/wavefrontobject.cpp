#include "wavefrontobject.h"

#include <GL/glut.h>

WavefrontObject::WavefrontObject()
    : Object()
{
}

void WavefrontObject::draw()
{
    glPushMatrix();

    if (quad)
    {
        renderQuads();
    }
    else
    {
        renderTriangles();
    }
    glPopMatrix();
}

void WavefrontObject::renderQuads()
{
    // TODO: Implement quad rendering
}

void WavefrontObject::renderTriangles()
{
    glBegin(GL_TRIANGLES);
    for (int j = 0 ; j < faces.size(); j++)
    {
        std::shared_ptr<Face3D> face = faces[j];

        //----------------- FIRST VERTEX -----------------
        //Normal coordinates of the first vertex
        glNormal3f(normals.at(face->normal[0] - 1)->x,
                   normals.at(face->normal[0] - 1)->y,
                   normals.at(face->normal[0] - 1)->z);

        // Texture coordinates of the first vertex
        glTexCoord2f(uvs.at(face->uv[0] - 1)->x,
                     uvs.at(face->uv[0] - 1)->y);

        // Coordinates of the first vertex
        glVertex3f(vertices.at(face->vertex[0] - 1)->x,
                   vertices.at(face->vertex[0] - 1)->y,
                   vertices.at(face->vertex[0] - 1)->z);




        //----------------- SECOND VERTEX -----------------
        //Normal coordinates of the first vertex
        glNormal3f(normals.at(face->normal[1] - 1)->x,
                   normals.at(face->normal[1] - 1)->y,
                   normals.at(face->normal[1] - 1)->z);

        // Texture coordinates of the first vertex
        glTexCoord2f(uvs.at(face->uv[1] - 1)->x,
                     uvs.at(face->uv[1] - 1)->y);

        // Coordinates of the first vertex
        glVertex3f(vertices.at(face->vertex[1] - 1)->x,
                   vertices.at(face->vertex[1] - 1)->y,
                   vertices.at(face->vertex[1] - 1)->z);




        //----------------- THIRD VERTEX -----------------
        //Normal coordinates of the first vertex
        glNormal3f(normals.at(face->normal[2] - 1)->x,
                   normals.at(face->normal[2] - 1)->y,
                   normals.at(face->normal[2] - 1)->z);

        // Texture coordinates of the first vertex
        glTexCoord2f(uvs.at(face->uv[2] - 1)->x,
                     uvs.at(face->uv[2] - 1)->y);

        // Coordinates of the first vertex
        glVertex3f( vertices.at(face->vertex[2] - 1)->x,
                    vertices.at(face->vertex[2] - 1)->y,
                    vertices.at(face->vertex[2] - 1)->z);



    }
    glEnd();
}
