#ifndef LINEAR_H
#define LINEAR_H
#include <cmath>
#include <vector>
#include <iostream>

// Three-Dimension Vector and Matrix.
class Vector3f{
	public:
	float x, y, z;

	public:
	Vector3f(){}
	// Constructor.
	Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
	// Squared size.
	float squared_size() { return x*x + y*y + z*z; }
	// The norm of the vector.
	float size(){ return sqrt(this->squared_size()); }
	// To normalize the vector.
	Vector3f normalize(){ return Vector3f(x/size(), y/size(), z/size()); }

	float& xx(){ float& x = this->x; return x; }
	float& yy(){ float& y = this->y; return y; }
	float& zz(){ float& z = this->z; return z; }
	float& operator[](int index){
		switch (index) {
			case 1: return xx();
			case 2: return yy();
			case 3: return zz();
			default: std::cerr << "VECTOR3F:OUT OF RANGE!" << std::endl; exit(-1);
		}
	}

	static float dot(Vector3f a, Vector3f b){
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}
};

inline Vector3f operator* (float k, Vector3f v){
	return Vector3f(k*v.x, k*v.y, k*v.z);
}
inline Vector3f operator+ (Vector3f a, Vector3f b){
	return Vector3f(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline Vector3f operator- (Vector3f a, Vector3f b){
	return Vector3f(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline bool operator==(Vector3f a, Vector3f b){
	return (
		(a.x == b.x) &&
		(a.y == b.y) &&
		(a.z == b.z)
	);
}

using Color = Vector3f;

/* ============================================ */
/* Four-Dimension Vectors and Matrix. */

class Vector4f{
	public:
	float x, y, z, w;

	public:
	Vector4f(){}
	// Constructors.
	Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4f(Vector3f a, float w) : x(a.x), y(a.y), z(a.z), w(w) {}
	Vector4f(Vector3f a) : x(a.x), y(a.y), z(a.z), w(1) {}
	Vector3f toLocation(){
		return Vector3f(x, y, z);
	}
	float& xx(){ float& x = this->x; return x; }
	float& yy(){ float& y = this->y; return y; }
	float& zz(){ float& z = this->z; return z; }
	float& ww(){ float& w = this->w; return w; }
	float& operator[](int index){
		switch (index) {
			case 0: return xx();
			case 1: return yy();
			case 2: return zz();
			case 3: return ww();
			default: std::cerr << "VECTOR4F:OUT OF RANGE!" << std::endl; exit(-1);
		}
	}

	static float dot(Vector4f a, Vector4f b){
		return a.x*b.x + a.y*b.y + a.z*b.z + a.w*a.w;
	}
};

class Matrix4f{
	public:
	Vector4f c[4];

	public:
	Matrix4f() {}
	Matrix4f(Vector4f a, Vector4f b, Vector4f c, Vector4f d) : c{a, b, c, d} {}

	Vector4f row(int index){
		return Vector4f(c[0][index], c[1][index], c[2][index], c[3][index]);
	}
	Vector4f col(int index){
		return Vector4f(c[index]);
	}

	static Matrix4f Identify(){
		return Matrix4f(
			Vector4f(1, 0, 0, 0),
			Vector4f(0, 1, 0, 0),
			Vector4f(0, 0, 1, 0),
			Vector4f(0, 0, 0, 1)
		);
	}

};

inline Matrix4f operator*(Matrix4f a, Matrix4f b){
	return Matrix4f(
		Vector4f(Vector4f::dot(a.row(0), b.col(0)),
		Vector4f::dot(a.row(1), b.col(0)),
		Vector4f::dot(a.row(2), b.col(0)),
		Vector4f::dot(a.row(3), b.col(0))),

		Vector4f(Vector4f::dot(a.row(0), b.col(1)),
		Vector4f::dot(a.row(1), b.col(1)),
		Vector4f::dot(a.row(2), b.col(1)),
		Vector4f::dot(a.row(3), b.col(1))),

		Vector4f(Vector4f::dot(a.row(0), b.col(2)),
		Vector4f::dot(a.row(1), b.col(2)),
		Vector4f::dot(a.row(2), b.col(2)),
		Vector4f::dot(a.row(3), b.col(2))),

		Vector4f(Vector4f::dot(a.row(0), b.col(3)),
		Vector4f::dot(a.row(1), b.col(3)),
		Vector4f::dot(a.row(2), b.col(3)),
		Vector4f::dot(a.row(3), b.col(3)))
	);
}

inline Vector4f operator*(Matrix4f m, Vector4f v){
	return Vector4f(
		Vector4f::dot(m.row(0), v),
		Vector4f::dot(m.row(1), v),
		Vector4f::dot(m.row(2), v),
		Vector4f::dot(m.row(3), v)
	);
}

inline Vector3f cross(Vector3f a, Vector3f b){
	return Vector3f(
		a.y*b.z - b.y*a.z,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}



#endif