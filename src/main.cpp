#include "window.h"
#include "vec3.h"
#include "ray.h"

using namespace std;

float hit_sphere(const vec3 center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1.0;
    else
        return (-b - sqrt(discriminant)) / (2.0 * a);
}

vec3 color(const ray& r)
{
    float t  = hit_sphere(vec3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = (r.point_at_parameter(t) - vec3(0, 0, -1)) / 0.5;
        return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    
    t = 0.5 * (r.direction().y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    int width = 1024;
    int height = 512;
    
    unsigned int *pixels = new unsigned int[width * height];
    
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    
    for (int j = height-1; j >= 0; j--)
    {
        for (int i=0; i < width; i++)
        {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            
            vec3 direction = unit_vector(lower_left_corner + (u * horizontal) + (v * vertical));

            ray r(origin, direction);
            vec3 col = color(r);

            // Converting to integers
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            int idx = width * (height-j-1) + i;
            pixels[idx] = (ir << 16) + (ig << 8) + ib;
        }
    }
    
    // Wait until the window is closed
    show_window(width, height, pixels);
    
    return EXIT_SUCCESS;
}



