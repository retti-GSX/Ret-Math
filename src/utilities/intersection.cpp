#include "../../include/utilities/intersection.hpp"

namespace Intersection {
    // 2D intersections
    bool pointInRect(const Vector2f& point, const Rectf& rect) {
        return point.x >= rect.left() && point.x <= rect.right() &&
               point.y >= rect.top() && point.y <= rect.bottom();
    }
    
    bool pointInCircle(const Vector2f& point, const Circlef& circle) {
        return (point - circle.center).lengthSquared() <= circle.radius * circle.radius;
    }
    
    bool rectsIntersect(const Rectf& a, const Rectf& b) {
        return !(b.left() > a.right() || b.right() < a.left() ||
                 b.top() > a.bottom() || b.bottom() < a.top());
    }
    
    bool circleRectIntersect(const Circlef& circle, const Rectf& rect) {
        Vector2f closestPoint = Vector2f(
            std::clamp(circle.center.x, rect.left(), rect.right()),
            std::clamp(circle.center.y, rect.top(), rect.bottom())
        );
        return (closestPoint - circle.center).lengthSquared() <= circle.radius * circle.radius;
    }
    
    bool circlesIntersect(const Circlef& a, const Circlef& b) {
        float distance = (a.center - b.center).length();
        return distance <= a.radius + b.radius && distance >= std::abs(a.radius - b.radius);
    }
    
    // Linear intersections 2D
    bool lineLine(const Vector2f& p1, const Vector2f& p2,
                  const Vector2f& p3, const Vector2f& p4,
                  Vector2f* intersection) {
        Vector2f dir1 = p2 - p1;
        Vector2f dir2 = p4 - p3;
        float denom = dir1.x * dir2.y - dir1.y * dir2.x;
        
        if (std::abs(denom) < 1e-6f) {
            return false;
        }
        
        float t = ((p1.x - p3.x) * dir2.y - (p1.y - p3.y) * dir2.x) / denom;
        float u = ((p1.x - p3.x) * dir1.y - (p1.y - p3.y) * dir1.x) / denom;
        
        if (intersection) {
            *intersection = p1 + dir1 * t;
        }
        
        return t >= 0 && t <= 1 && u >= 0 && u <= 1;
    }
    
    bool lineRect(const Vector2f& p1, const Vector2f& p2,
                  const Rectf& rect, Vector2f* entry,
                  Vector2f* exit) {
        Vector2f dir = p2 - p1;
        Vector2f invDir = Vector2f(1.0f / dir.x, 1.0f / dir.y);
        
        float t1 = (rect.left() - p1.x) * invDir.x;
        float t2 = (rect.right() - p1.x) * invDir.x;
        float t3 = (rect.top() - p1.y) * invDir.y;
        float t4 = (rect.bottom() - p1.y) * invDir.y;
        
        float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), 0.0f);
        float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), 1.0f);
        
        if (tmax < 0 || tmin > tmax) {
            return false;
        }
        
        if (entry) {
            *entry = p1 + dir * tmin;
        }
        if (exit) {
            *exit = p1 + dir * tmax;
        }
        
        return true;
    }
    
    bool lineCircle(const Vector2f& p1, const Vector2f& p2,
                    const Circlef& circle, Vector2f* entry,
                    Vector2f* exit) {
        Vector2f dir = p2 - p1;
        Vector2f toCenter = circle.center - p1;
        float a = dir.dot(dir);
        float b = 2 * toCenter.dot(dir);
        float c = toCenter.dot(toCenter) - circle.radius * circle.radius;
        float discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0) {
            return false;
        }
        
        discriminant = std::sqrt(discriminant);
        float t1 = (-b - discriminant) / (2 * a);
        float t2 = (-b + discriminant) / (2 * a);
        
        if (entry) {
            *entry = p1 + dir * t1;
        }
        if (exit) {
            *exit = p1 + dir * t2;
        }
        
        return true;
    }
    
    // 3D intersections
    bool pointInAABB(const Vector3f& point, const AABBf& aabb) {
        return point.x >= aabb.min.x && point.x <= aabb.max.x &&
               point.y >= aabb.min.y && point.y <= aabb.max.y &&
               point.z >= aabb.min.z && point.z <= aabb.max.z;
    }
    
    bool pointInSphere(const Vector3f& point, const Vector3f& center, float radius) {
        return (point - center).lengthSquared() <= radius * radius;
    }
    
    bool aabbsIntersect(const AABBf& a, const AABBf& b) {
        return !(b.max.x < a.min.x || b.min.x > a.max.x ||
                 b.max.y < a.min.y || b.min.y > a.max.y ||
                 b.max.z < a.min.z || b.min.z > a.max.z);
    }
    
    bool sphereSphereIntersect(const Vector3f& c1, float r1,
                               const Vector3f& c2, float r2) {
        float distance = (c1 - c2).length();
        return distance <= r1 + r2 && distance >= std::abs(r1 - r2);
    }
    
    bool sphereAABBIntersect(const Vector3f& center, float radius,
                             const AABBf& aabb) {
        Vector3f closestPoint = Vector3f(
            std::clamp(center.x, aabb.min.x, aabb.max.x),
            std::clamp(center.y, aabb.min.y, aabb.max.y),
            std::clamp(center.z, aabb.min.z, aabb.max.z)
        );
        return (closestPoint - center).lengthSquared() <= radius * radius;
    }
    
    // Ray intersections
    bool rayPlane(const Ray<float>& ray, const Plane<float>& plane,
                  float& t, Vector3f* intersection) {
        float denominator = ray.direction.dot(plane.getNormal());
        if (std::abs(denominator) < 1e-6f) {
            return false;
        }
        t = -(ray.origin.dot(plane.getNormal()) + plane.getDistance()) / denominator;
        if (intersection) {
            *intersection = ray.pointAt(t);
        }
        return true;
    }
    
    bool rayAABB(const Ray<float>& ray, const AABBf& aabb,
                 float& tMin, float& tMax,
                 Vector3f* entry, Vector3f* exit) {
        Vector3f invDir = Vector3f(1.0f / ray.direction.x, 1.0f / ray.direction.y, 1.0f / ray.direction.z);
        
        float t1 = (aabb.min.x - ray.origin.x) * invDir.x;
        float t2 = (aabb.max.x - ray.origin.x) * invDir.x;
        float t3 = (aabb.min.y - ray.origin.y) * invDir.y;
        float t4 = (aabb.max.y - ray.origin.y) * invDir.y;
        float t5 = (aabb.min.z - ray.origin.z) * invDir.z;
        float t6 = (aabb.max.z - ray.origin.z) * invDir.z;
        
        tMin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        tMax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
        
        if (tMax < 0 || tMin > tMax) {
            return false;
        }
        
        if (entry) {
            *entry = ray.pointAt(tMin);
        }
        if (exit) {
            *exit = ray.pointAt(tMax);
        }
        
        return true;
    }
    
    bool raySphere(const Ray<float>& ray, const Vector3f& center, float radius,
                   float& t1, float& t2,
                   Vector3f* point1, Vector3f* point2) {
        Vector3f toCenter = center - ray.origin;
        float a = ray.direction.dot(ray.direction);
        float b = 2 * toCenter.dot(ray.direction);
        float c = toCenter.dot(toCenter) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0) {
            return false;
        }
        
        discriminant = std::sqrt(discriminant);
        t1 = (-b - discriminant) / (2 * a);
        t2 = (-b + discriminant) / (2 * a);
        
        if (point1) {
            *point1 = ray.pointAt(t1);
        }
        if (point2) {
            *point2 = ray.pointAt(t2);
        }
        
        return true;
    }
    
    bool rayTriangle(const Ray<float>& ray, const Vector3f& v0,
                     const Vector3f& v1, const Vector3f& v2,
                     float& t, Vector3f* barycentric,
                     Vector3f* normal) {
        Vector3f edge1 = v1 - v0;
        Vector3f edge2 = v2 - v0;
        Vector3f h = ray.direction.cross(edge2);
        float a = edge1.dot(h);
         
        if (a > -1e-6f && a < 1e-6f) {
            return false;
        }
         
        float f = 1.0f / a;
        Vector3f s = ray.origin - v0;
        float u = f * s.dot(h);
         
        if (u < 0.0f || u > 1.0f) {
            return false;
        }
         
        Vector3f q = s.cross(edge1);
        float v = f * ray.direction.dot(q);
         
        if (v < 0.0f || u + v > 1.0f) {
            return false;
        }
         
        t = f * edge2.dot(q);
         
        if (t > 1e-6f) {
            if (barycentric) {
                *barycentric = Vector3f(1.0f - u - v, u, v);
            }
            if (normal) {
                *normal = edge1.cross(edge2).normalized();
            }
            return true;
        }
         
        return false;
    }
    
    // New intersection functions for geometric classes
    bool raySphere(const Ray<float>& ray, const Spheref& sphere,
                   float& t1, float& t2,
                   Vector3f* point1, Vector3f* point2) {
        return raySphere(ray, sphere.center, sphere.radius, t1, t2, point1, point2);
    }
    
    bool rayTriangle(const Ray<float>& ray, const Trianglef& triangle,
                     float& t, Vector3f* barycentric,
                     Vector3f* normal) {
        return rayTriangle(ray, triangle.a, triangle.b, triangle.c, t, barycentric, normal);
    }
    
    bool sphereSphere(const Spheref& s1, const Spheref& s2) {
        return sphereSphereIntersect(s1.center, s1.radius, s2.center, s2.radius);
    }
    
    bool aabbAABB(const AABBf& a, const AABBf& b) {
        return aabbsIntersect(a, b);
    }
    
    // Frustum intersections (for camera)
    bool aabbInFrustum(const AABBf& aabb, const Frustum& frustum) {
        for (int i = 0; i < 6; ++i) {
            if (aabb.classifyPlane(frustum.planes[i].getNormal(), frustum.planes[i].getDistance()) == AABBf::PlaneIntersection::Back) {
                return false;
            }
        }
        return true;
    }
    
    bool sphereInFrustum(const Vector3f& center, float radius,
                         const Frustum& frustum) {
        for (int i = 0; i < 6; ++i) {
            float distance = frustum.planes[i].distanceToPoint(center);
            if (distance < -radius) {
                return false;
            }
        }
        return true;
    }
    
    // 3D volume intersections
    bool aabbTriangle(const AABBf& aabb, const Vector3f& v0,
                      const Vector3f& v1, const Vector3f& v2) {
        Vector3f center = aabb.center();
        Vector3f extents = aabb.extents();
        Vector3f edge1 = v1 - v0;
        Vector3f edge2 = v2 - v0;
        Vector3f normal = edge1.cross(edge2).normalized();
        
        float p0 = normal.dot(v0);
        float p1 = normal.dot(v1);
        float p2 = normal.dot(v2);
        float minP = std::min(std::min(p0, p1), p2);
        float maxP = std::max(std::max(p0, p1), p2);
        
        float distance = normal.dot(center);
        float radius = extents.x * std::abs(normal.x) + extents.y * std::abs(normal.y) + extents.z * std::abs(normal.z);
        
        return !(distance + radius < minP || distance - radius > maxP);
    }
    
    // SAT (Separating Axis Theorem) for convex polygons
    bool satTest2D(const std::vector<Vector2f>& poly1,
                   const std::vector<Vector2f>& poly2) {
        std::vector<Vector2f> axes;
        
        for (size_t i = 0; i < poly1.size(); ++i) {
            Vector2f edge = poly1[(i + 1) % poly1.size()] - poly1[i];
            Vector2f normal = Vector2f(-edge.y, edge.x).normalized();
            axes.push_back(normal);
        }
        
        for (size_t i = 0; i < poly2.size(); ++i) {
            Vector2f edge = poly2[(i + 1) % poly2.size()] - poly2[i];
            Vector2f normal = Vector2f(-edge.y, edge.x).normalized();
            axes.push_back(normal);
        }
        
        for (const auto& axis : axes) {
            float min1 = std::numeric_limits<float>::max();
            float max1 = -std::numeric_limits<float>::max();
            float min2 = std::numeric_limits<float>::max();
            float max2 = -std::numeric_limits<float>::max();
            
            for (const auto& point : poly1) {
                float projection = point.dot(axis);
                min1 = std::min(min1, projection);
                max1 = std::max(max1, projection);
            }
            
            for (const auto& point : poly2) {
                float projection = point.dot(axis);
                min2 = std::min(min2, projection);
                max2 = std::max(max2, projection);
            }
            
            if (max1 < min2 || max2 < min1) {
                return false;
            }
        }
        
        return true;
    }
    
    // Intersection point calculation
    Vector3f computeIntersectionPoint(const Ray<float>& ray, float t) {
        return ray.pointAt(t);
    }
    
    // Distance between objects
    float distancePointToLine(const Vector3f& point,
                              const Vector3f& lineStart,
                              const Vector3f& lineEnd) {
        Vector3f lineDir = lineEnd - lineStart;
        Vector3f toPoint = point - lineStart;
        float t = toPoint.dot(lineDir) / lineDir.dot(lineDir);
        t = std::clamp(t, 0.0f, 1.0f);
        Vector3f closestPoint = lineStart + lineDir * t;
        return (point - closestPoint).length();
    }
    
    float distancePointToPlane(const Vector3f& point,
                               const Vector3f& planePoint,
                               const Vector3f& planeNormal) {
        return std::abs((point - planePoint).dot(planeNormal)) / planeNormal.length();
    }
    
    // Point classification relative to plane
    PlaneSide classifyPointToPlane(const Vector3f& point,
                                   const Vector3f& planePoint,
                                   const Vector3f& planeNormal) {
        float distance = (point - planePoint).dot(planeNormal);
        if (distance > 1e-6f) {
            return PlaneSide::Front;
        } else if (distance < -1e-6f) {
            return PlaneSide::Back;
        }
        return PlaneSide::OnPlane;
    }
    
    // 3D segment intersections
    bool segmentSegment(const Vector3f& p1, const Vector3f& p2,
                        const Vector3f& q1, const Vector3f& q2,
                        float& t, float& u, Vector3f* intersection) {
        Vector3f dir1 = p2 - p1;
        Vector3f dir2 = q2 - q1;
        Vector3f cross = dir1.cross(dir2);
        float denom = cross.dot(cross);
        
        if (denom < 1e-6f) {
            return false;
        }
        
        Vector3f toQ1 = q1 - p1;
        t = toQ1.cross(dir2).dot(cross) / denom;
        u = toQ1.cross(dir1).dot(cross) / denom;
        
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            if (intersection) {
                *intersection = p1 + dir1 * t;
            }
            return true;
        }
        
        return false;
    }
    
    // Ray-cylinder intersection
    bool rayCylinder(const Ray<float>& ray, const Vector3f& base,
                     const Vector3f& axis, float radius, float height,
                     float& t1, float& t2) {
        Vector3f toBase = base - ray.origin;
        Vector3f axisNormalized = axis.normalized();
        float axisDotDir = axisNormalized.dot(ray.direction);
        float axisDotToBase = axisNormalized.dot(toBase);
        
        float a = 1 - axisDotDir * axisDotDir;
        float b = toBase.dot(ray.direction) - axisDotDir * axisDotToBase;
        float c = toBase.dot(toBase) - axisDotToBase * axisDotToBase - radius * radius;
        float discriminant = b * b - a * c;
        
        if (discriminant < 0) {
            return false;
        }
        
        discriminant = std::sqrt(discriminant);
        t1 = (-b - discriminant) / a;
        t2 = (-b + discriminant) / a;
        
        float tMin = std::min(t1, t2);
        float tMax = std::max(t1, t2);
        
        float heightMin = axisDotToBase + axisDotDir * tMin;
        float heightMax = axisDotToBase + axisDotDir * tMax;
        
        if (heightMin > height || heightMax < 0) {
            return false;
        }
        
        return true;
    }
    
    // Ray-disk intersection
    bool rayDisk(const Ray<float>& ray, const Vector3f& center,
                 const Vector3f& normal, float radius,
                 float& t, Vector3f* intersection) {
        float denominator = ray.direction.dot(normal);
        if (std::abs(denominator) < 1e-6f) {
            return false;
        }
         
        t = (center - ray.origin).dot(normal) / denominator;
        Vector3f point = ray.pointAt(t);
        Vector3f toPoint = point - center;
         
        if (toPoint.lengthSquared() <= radius * radius) {
            if (intersection) {
                *intersection = point;
            }
            return true;
        }
         
        return false;
    }
    
    // Triangle mathematics
    Vector3f triangleNormal(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2) {
        Vector3f edge1 = v1 - v0;
        Vector3f edge2 = v2 - v0;
        return edge1.cross(edge2).normalized();
    }
    
    float triangleArea(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2) {
        Vector3f edge1 = v1 - v0;
        Vector3f edge2 = v2 - v0;
        return edge1.cross(edge2).length() * 0.5f;
    }
    
    Vector3f triangleBarycentric(const Vector3f& point, const Vector3f& v0,
                                 const Vector3f& v1, const Vector3f& v2) {
        Vector3f v01 = v1 - v0;
        Vector3f v02 = v2 - v0;
        Vector3f v0p = point - v0;
        
        float d00 = v01.dot(v01);
        float d01 = v01.dot(v02);
        float d11 = v02.dot(v02);
        float d20 = v0p.dot(v01);
        float d21 = v0p.dot(v02);
        
        float denom = d00 * d11 - d01 * d01;
        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        float u = 1.0f - v - w;
        
        return Vector3f(u, v, w);
    }
}