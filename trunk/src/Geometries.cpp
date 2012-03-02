//
// Geometries.cpp for gle in /home/michar_l//glEngine
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Feb 20 22:34:18 2012 loick michard
// Last update Thu Mar  1 22:31:25 2012 loick michard
//

#include <cmath>
#include <Geometries.hpp>
#include <Array.hpp>
#include <vector>

gle::Mesh* gle::Geometries::Cube(gle::Material* material, GLfloat size)
{
  return (Cuboid(material, size, size, size));
}

gle::Mesh* gle::Geometries::Cuboid(gle::Material* material, 
				   GLfloat width, GLfloat height,
				   GLfloat depth)
{
  GLfloat halfWidth = width / 2;
  GLfloat halfHeight = height / 2;
  GLfloat halfDepth = depth / 2;
  
  GLfloat vertexes[] = {
    //! Top face
   -halfWidth, halfHeight,  -halfDepth,
   halfWidth, halfHeight,  -halfDepth,
   halfWidth, halfHeight,  halfDepth,
   -halfWidth, halfHeight,  halfDepth,
   
    //! bottom face
   -halfWidth, -halfHeight,  -halfDepth,
   halfWidth, -halfHeight,  -halfDepth,
   halfWidth, -halfHeight,  halfDepth,
   -halfWidth, -halfHeight,  halfDepth,

    //! Front face
   -halfWidth, halfHeight,  -halfDepth,
   -halfWidth, -halfHeight,  -halfDepth,
   halfWidth, -halfHeight,  -halfDepth,
   halfWidth, halfHeight,  -halfDepth,

    //! Back face
   -halfWidth, -halfHeight,  halfDepth,
   halfWidth, -halfHeight,  halfDepth,
   halfWidth, halfHeight,  halfDepth,
   -halfWidth, halfHeight,  halfDepth,

    //! Right face
   halfWidth, -halfHeight,  -halfDepth,
   halfWidth, -halfHeight,  halfDepth,
   halfWidth, halfHeight,  halfDepth,
   halfWidth, halfHeight,  -halfDepth,

    //! Left face
   -halfWidth, halfHeight,  -halfDepth,
   -halfWidth, -halfHeight,  -halfDepth,
   -halfWidth, -halfHeight,  halfDepth,
   -halfWidth, halfHeight,  halfDepth,
  };
  
  GLuint indexes[] = {
    0, 1, 2, 0, 2, 3, //! Front face
    4, 5, 6, 4, 6, 7, //! Back face
    8, 9, 10, 8, 10, 11, //! Top face
    12, 13, 14, 12, 14, 15, //! Bottom face
    16, 17, 18, 16, 18, 19, //! Right face
    20, 21, 22, 20, 22, 23 //! Left face
  };

  GLfloat normals[] = {
    //! Top face
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,

    //! Bottom face
    0.0, -1.0,  0.0,
    0.0, -1.0,  0.0,
    0.0, -1.0,  0.0,
    0.0, -1.0,  0.0,

    //! Front face
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,

    //! Back face
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,
    0.0,  0.0, -1.0,

    //! Right face
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,

    //! Left face
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0
  };

  GLfloat textureCoords[] = {
    // Front face
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,

    // Back face
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    0.0, 0.0,

    // Top face
    0.0, 1.0,
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,

    // Bottom face
    1.0, 1.0,
    0.0, 1.0,
    0.0, 0.0,
    1.0, 0.0,

    // Right face
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    0.0, 0.0,

    // Left face
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0
  };

  gle::Mesh *cuboid = new gle::Mesh(material,
				    vertexes,
				    sizeof(vertexes) / sizeof(GLfloat),
				    normals, sizeof(normals) / sizeof(GLfloat),
				    indexes, sizeof(indexes) / sizeof(GLuint));
  cuboid->setTextureCoords(textureCoords,
			   sizeof(textureCoords) / sizeof(GLfloat));
  return (cuboid);
}

gle::Mesh* gle::Geometries::Sphere(gle::Material* material,
				   GLfloat radius,
				   GLint slices, GLint stacks)
{
  std::vector<GLfloat> vertexes;
  std::vector<GLfloat> normals;
  std::vector<GLuint> indexes;
  gle::Array<GLfloat> uv;

  for (GLfloat sl = 0; sl <= slices; ++sl)
    {
      GLfloat theta = sl * M_PI / slices;
      for (GLfloat st = 0; st <= stacks; ++st)
	{
	  GLfloat phi = st * 2.0 * M_PI / stacks;
	  GLfloat x = sin(theta) * cos(phi);
	  GLfloat y = cos(theta);
	  GLfloat z = sin(theta) * sin(phi);

	  vertexes.push_back(x * radius);
	  vertexes.push_back(y * radius);
	  vertexes.push_back(z * radius);
	  normals.push_back(x);
	  normals.push_back(y);
	  normals.push_back(z);
	  uv.push_back(1.0 - (st / stacks));
	  uv.push_back(sl / slices);
	  if (sl != slices && st != stacks)
	    {
	      GLfloat indice1 = sl * (stacks + 1) + st;
	      GLfloat indice2 = indice1 + stacks + 1;
	      indexes.push_back(indice1);
	      indexes.push_back(indice2);
	      indexes.push_back(indice1 + 1);
	      indexes.push_back(indice2);
	      indexes.push_back(indice2 + 1);
	      indexes.push_back(indice1 + 1);
	    }
	}
    }
  gle::Mesh * ret = new gle::Mesh(material, &vertexes[0], vertexes.size(),
				  &normals[0], normals.size(),
				  &indexes[0], indexes.size());
  ret->setTextureCoords(uv);
  return (ret);
}