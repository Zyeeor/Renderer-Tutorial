#ifndef RASTERIZATION_H
#define RASTERIZATION_H
#include "Linear.h"
#include "Camera.h"
#include "opencv2/core/mat.hpp"
#include <vector>

// The function used to rasterize a triangle.
std::vector<Color> Rasterization(std::vector<Vector3f> vertices, Camera camera);

// Display the known pixels on screen.
void Display(std::vector<Color> fragments);

// The function used to produce projection matrix.
Matrix4f projection_matrix(Camera camera, Vector3f location);

// The function used to tell if a pixel in a specific triangle.
bool isInTriangle(Vector3f location, std::vector<Vector3f> trianglePoints);

void Display(std::vector<Color> pixels, Camera camera);

#endif