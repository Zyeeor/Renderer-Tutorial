#ifndef CAMERA_H
#define CAMERA_H

#include "Linear.h"
#include <iostream>
class Camera{
	public:
	int screen_width, screen_height;
	const float view_width = 1;
	float view_height;
	float view_ratio;
	float FoV, depth;
	Vector3f location;
	Vector3f view_direction;
	Vector3f up_direction;

	public:
	Camera(){}
	Camera(int width, int height, Vector3f location, Vector3f view_direction, Vector3f up_direction, float FoV, float depth) :
		screen_width(width), screen_height(height), view_ratio((float)width/height), view_height((float)height/width),
		location(location), view_direction(view_direction), up_direction(up_direction), FoV(FoV), depth(depth) {}
	Matrix4f view_matrix(){
		Matrix4f translation(
			Vector4f(1, 0, 0, 0),
			Vector4f(0, 1, 0, 0),
			Vector4f(0, 0, 1, 0),
			Vector4f(-location.x, -location.y, -location.z, 1)
		);
		auto direction = view_direction.normalize();
		auto updirection = up_direction.normalize();
		float yz_angle_cosine = Vector3f::dot(direction, Vector3f(0, 0, -1));
		float xz_angle_cosine = Vector3f::dot(direction, Vector3f(0, 0, -1));
		float xy_angle_cosine = Vector3f::dot(updirection, Vector3f(0, 1, 0));
		float xy_angle_sine = -sqrt(1 - xy_angle_cosine*xy_angle_cosine);
		float xz_angle_sine = -sqrt(1 - xz_angle_cosine*xz_angle_cosine);
		float yz_angle_sine = -sqrt(1 - yz_angle_cosine*yz_angle_cosine);
		
		Matrix4f xy_rotation = Matrix4f(
			Vector4f(xy_angle_cosine, xy_angle_sine, 0, 0),
			Vector4f(-xy_angle_sine, xy_angle_cosine, 0, 0),
			Vector4f(0, 0, 1, 0),
			Vector4f(0, 0, 0, 1)
		);
		Matrix4f xz_rotation = Matrix4f(
			Vector4f(xz_angle_cosine, 0, -xz_angle_sine, 0),
			Vector4f(0, 1, 0, 0),
			Vector4f(xz_angle_sine, 0, xz_angle_cosine, 0),
			Vector4f(0, 0, 0, 1)
		);
		Matrix4f yz_rotation = Matrix4f(
			Vector4f(1, 0, 0, 0),
			Vector4f(0, yz_angle_cosine, yz_angle_sine, 0),
			Vector4f(0, -yz_angle_sine, yz_angle_cosine, 0),
			Vector4f(0, 0, 0, 1)
		);
		return xz_rotation * yz_rotation * xy_rotation * translation;
	}
};

#endif