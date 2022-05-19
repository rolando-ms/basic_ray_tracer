#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable{
    public:
        sphere(){}
        sphere(point3 cen, double r) : center(cen), radius(r) {};
        
        virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
        
     public:
        point3 center;
        double radius;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const{
    // Solving b*bt^2 + 2b*(A-C)t + (A-C)*(A-C)-r^2 = 0 with discriminant(from gral soln)
    // Eqn is simplified using b^2 = 2h
    vec3 oc{r.origin() - center};
    auto a{r.direction().length_squared()};
    auto half_b{dot(oc, r.direction())};
    auto c{oc.length_squared() - radius*radius};
    
    auto discriminant{half_b*half_b - a*c};
    if(discriminant < 0) return false;
    auto sqrtd{sqrt(discriminant)};
    
    // Find nearest root in range (t_min, t_max)
    auto root{(-half_b - sqrtd) / a};
    if(root < t_min || t_max < root) return false;
    
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal{(rec.p - center) / radius};
    rec.set_face_normal(r, outward_normal);
    
    return true;
}

#endif