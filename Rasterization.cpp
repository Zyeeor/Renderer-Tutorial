#include "Rasterization.h"
#include "Camera.h"
#include "Linear.h"
#include <iostream>
#include <vector>

Matrix4f projection_matrix(Camera camera, Vector3f location) {
	float near = -camera.view_height * camera.FoV;
	float far = location.z;
	return Matrix4f(
		Vector4f(near/far, 0, 0, 0),
		Vector4f(0, near/far, 0, 0),
		Vector4f(0, 0, near/far, 0),
		Vector4f(0, 0, 0, 1)
	);
}

std::vector<Color> Rasterization(std::vector<Vector3f> vertices, Camera camera){
	//std::cerr << "Rasterize is running." << std::endl;
	std::vector<Vector3f> tri(3);
	float near = -camera.view_height * camera.FoV;
	std::vector<Color> pixel_colors;
	Color pixel;
	for(auto &vertex: vertices){
		//std::cerr << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
		Vector4f v = projection_matrix(camera, vertex)*camera.view_matrix()*Vector4f(vertex, 1);
		vertex = v.toLocation();
		//std::cerr << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
	}
	
	float x, y, z;
	z = near;
	//std::cerr << "plane near: " << z << std::endl;
	for(int j = camera.screen_height - 1; j >= 0; j--){
		for(int i = 0; i < camera.screen_width; i++){
			for(int k = 0; k < vertices.size(); k += 3){
			tri[0] = vertices[k];
			tri[1] = vertices[k+1];
			tri[2] = vertices[k+2];
			x = ((float)i+0.5)/camera.screen_width;
			x = (x - 0.5)*camera.view_width;
			y = ((float)j+0.5)/camera.screen_height;
			y = (y-0.5)*camera.view_height;
			if(isInTriangle(Vector3f(x,y,z), tri) == true){
				pixel_colors.push_back(Color(0.6, 0, 0));
			}else{
				pixel_colors.push_back(Color(0, 0, 0));
			}
			}
		}
	}
	//std::cerr << "Rasterize is ok." << std::endl;
	return pixel_colors;
}

bool isInTriangle(Vector3f location, std::vector<Vector3f> trianglePoints){
	const Vector3f& P = 10000 * location;
	const Vector3f& A = 10000 * trianglePoints[0];
    const Vector3f& B = 10000 * trianglePoints[1];
    const Vector3f& C = 10000 * trianglePoints[2];


    Vector3f AP = A - P;
    Vector3f BP = B - P;
    Vector3f CP = C - P;


    float z1 = cross(AP, BP).z;
    float z2 = cross(BP, CP).z;
    float z3 = cross(CP, AP).z;

    if ((z1 > 0 && z2 >0 && z3 > 0) ||  (z1 < 0 && z2 <0 && z3 < 0)){
		return true;
	}else{
		return false;
	};
}

void Display(std::vector<Color> pixels, Camera camera){
	int count = 0;
	auto height = camera.screen_height;
	auto width = camera.screen_width;
	std::cout << "P3\n" << width << ' ' << height << "\n255\n";
	for (int j = height-1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            int ir = static_cast<int>(255.999*pixels[i+count].x);
            int ig = static_cast<int>(255.999*pixels[i+count].y);
            int ib = static_cast<int>(255.999*pixels[i+count].z);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
		count += width;
    }
}