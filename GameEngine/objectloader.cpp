#include "objectloader.h"

#include <vector>
#include <cstring>
#include "GameEngine/coord2d.h"
#include "GameEngine/coord3d.h"
#include <iostream>
#include "GameEngine/face3d.h"

// Code taken and modified from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// So credits to opengl-tutorial.org

std::shared_ptr<WavefrontObject> ObjectLoader::loadObject(std::string filePath)
{
    auto object = std::make_shared<WavefrontObject>();

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    std::vector<std::shared_ptr<Coord3D>> out_vertices;
    std::vector<std::shared_ptr<Coord2D>> out_uvs;
    std::vector<std::shared_ptr<Coord3D>> out_normals;

    std::vector<std::shared_ptr<Coord3D>> temp_vertices;

    std::vector<std::shared_ptr<Coord2D>> temp_uvs;
    std::vector<std::shared_ptr<Coord3D>> temp_normals;

    std::shared_ptr<std::shared_ptr<Face3D>> faces;

    FILE * file = fopen(filePath.c_str(), "r");
    if( file == NULL )
    {
        std::cout << "Cannot open the file \"" + filePath + "\"!\n" << std::endl;
        return nullptr;
    }

    while(1)
    {
        char lineHeader[128];
        // Read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
        {
            break; // EOF = End Of File. Quit the loop.
        }

        if (strcmp(lineHeader, "#") == 0)
        {
            // Ignore
        }
        else if (strcmp(lineHeader, "v") == 0)
        {
            auto vertex = std::make_shared<Coord3D>();
            fscanf(file, "%f %f %f\n", &vertex->x, &vertex->y, &vertex->z );
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
            auto uv = std::make_shared<Coord2D>();
            fscanf(file, "%f %f\n", &uv->x, &uv->y );
            temp_uvs.push_back(uv);
        }
        else if (strcmp( lineHeader, "vn") == 0)
        {
            auto normal = std::make_shared<Coord3D>();
            fscanf(file, "%f %f %f\n", &normal->x, &normal->y, &normal->z );
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            // TODO: Add ability to load Quads

            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9)
            {
                std::cout << "File can't be read by our simple parser : ( Try exporting with other options\n" << std::endl;
                return nullptr;
            }

            auto face = std::make_shared<Face3D>(false);
            face->vertex[0] = vertexIndex[0];
            face->vertex[1] = vertexIndex[1];
            face->vertex[2] = vertexIndex[2];

            face->uv[0] = uvIndex[0];
            face->uv[1] = uvIndex[1];
            face->uv[2] = uvIndex[2];

            face->normal[0] = normalIndex[0];
            face->normal[1] = normalIndex[1];
            face->normal[2] = normalIndex[2];

            object->faces.push_back(face);
        }
    }

    object->normals = temp_normals;
    object->uvs = temp_uvs;
    object->vertices = temp_vertices;

    return object;
}
