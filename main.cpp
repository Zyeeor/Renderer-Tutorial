//#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <ostream>
#include <vector>
#include "Linear.h"
#include "Camera.h"
#include "Rasterization.h"

int main(){
	int width = 800, height = 600;
	Color red(0.5, 0, 0);
	Color black(0.1, 0.15, 0.1);
	Color current;
	Camera camera(width, height, Vector3f(0, 0, 0), Vector3f(0, 0, -1), Vector3f(0, 1, 0), 1.0f, 10);
	std::vector<Vector3f> triangle = {
		Vector3f(-1, -1, -3),
		Vector3f(1, -1, -3),
		Vector3f(0, 1, -3)
	};
	auto pixels = Rasterization(triangle, camera);
	Display(pixels, camera);
	return 0;
}
