#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

// Solving b*bt^2 + 2b*(A-C)t + (A-C)*(A-C)-r^2 = 0 with discriminant(from gral soln)
double hit_sphere(const point3 &center, double radius, const ray &r){
    vec3 oc{r.origin() - center};
    auto a{r.direction().length_squared()};
    auto half_b{dot(oc, r.direction())};
    auto c{oc.length_squared() - radius * radius};
    auto discriminant{half_b*half_b - a*c};
    if(discriminant < 0){
        return -1.0;
    } else{
        return (-half_b - sqrt(discriminant)) / (a);
    }
}

color ray_color(const ray &r){
    // If hit sphere, then color is red
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    
    // Using normals to hit point to color the sphere
    if(t > 0.0){
        vec3 N{unit_vector(r.at(t) - vec3(0,0,-1))}; // N = P-C ; hitpoint - sphere center
        return 0.5 * color(N.x()+1, N.y()+1, N.z()+1); // Normalizing to [0,1]
    }
    
    vec3 unit_direction{unit_vector(r.direction())};
    
    // Normilize [0-1]
    t = 0.5 * (unit_direction.y() + 1.0);
    
    // Linear interpolation (white to blue)
    return (1.0-t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
	// Image info
    const auto aspect_ratio{16.0/9.0};
    const int image_width{400};
    const int image_height{static_cast<int>(image_width / aspect_ratio)};
    
    // Camera parameters
    auto viewport_height{2.0};
    auto viewport_width{aspect_ratio * viewport_height};
    auto focal_length{1.0};
    
    auto origin{point3(0, 0, 0)};
    auto horizontal{vec3(viewport_width, 0, 0)};
    auto vertical{vec3(0, viewport_height, 0)};
    auto lower_left_corner{origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length)};
    
    // Rendering image
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    // Rows written top to bottom
    for(int j{image_height - 1}; j >= 0; --j){
        std::cerr << "\rRemaining rows: " << j << ' ' << std::flush;
        
        // Columns written left to right
        for(int i{0}; i < image_width; ++i){
            auto u{double(i) / (image_width-1)};
            auto v{double(j) / (image_height-1)};
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color{ray_color(r)};
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nFinished.\n";
}
