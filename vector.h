#include <math.h>
#define PI 3.1415926535
#define deg_to_rad(angle) ((angle * PI)/180)
#define rad_to_deg(angle) ((angle * 180)/PI)

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

Vector3 create_vector(float x, float y, float z) {
    Vector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vector3 add_vector(Vector3 v1, Vector3 v2) {
    return create_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 subtract_vector(Vector3 v1, Vector3 v2) {
    return create_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 get_rotated_vector(float x, float y, float z, Vector3 v) {
    // Rotated relative to world origin
    x = deg_to_rad(x);
    y = deg_to_rad(y);
    z = deg_to_rad(z);
    float i = (v.x*cos(y)*cos(z)) + (v.y*(sin(x)*sin(y)*cos(z) - cos(x)*sin(z))) + (v.z*(cos(x)*sin(y)*cos(z) + sin(x)*sin(z)));
    float j = (v.x*cos(y)*sin(z)) + (v.y*(sin(x)*sin(y)*sin(z) + cos(x)*cos(z))) + (v.z*(cos(x)*sin(y)*sin(z) - sin(x)*cos(z)));
    float k = (v.x*-1*sin(y)) + (v.y*sin(x)*cos(y)) + (v.z*cos(x)*cos(y));
    return create_vector(i, j, k);
}

Vector3 get_relative_rotated_vector(float x, float y, float z, Vector3 v, Vector3 rel) {
    // Rotated relative to Vector3 rel
    return add_vector(rel, get_rotated_vector(x, y, z, subtract_vector(v, rel)));
}

void show_vector(Vector3 v) {
    printf("Vector3(%f, %f, %f)\n", v.x, v.y, v.z);
}

int is_zero_vector(Vector3 v) {
    return (v.x == 0) && (v.y == 0) && (v.z == 0);
}
