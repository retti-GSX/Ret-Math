#pragma once
#include <vector>
#include <array>
#include "../vectors/vector2.hpp"
#include "../vectors/vector3.hpp"
#include "../geometry/ray.hpp"
#include "../geometry/plane.hpp"
#include "../geometry/rect.hpp"
#include "../geometry/circle.hpp"
#include "../geometry/aabb.hpp"
#include "../geometry/sphere.hpp"
#include "../geometry/triangle.hpp"
#include "../geometry/obb.hpp"
#include "../geometry/capsule.hpp"
#include <cmath>
#include <algorithm>

namespace Intersection {
    // 2D intersections
    bool pointInRect(const Vector2f& point, const Rectf& rect);
    bool pointInCircle(const Vector2f& point, const Circlef& circle);
    bool rectsIntersect(const Rectf& a, const Rectf& b);
    bool circleRectIntersect(const Circlef& circle, const Rectf& rect);
    bool circlesIntersect(const Circlef& a, const Circlef& b);
     
    // Linear intersections 2D
    bool lineLine(const Vector2f& p1, const Vector2f& p2,
                  const Vector2f& p3, const Vector2f& p4,
                  Vector2f* intersection = nullptr);
    bool lineRect(const Vector2f& p1, const Vector2f& p2,
                  const Rectf& rect, Vector2f* entry = nullptr,
                  Vector2f* exit = nullptr);
    bool lineCircle(const Vector2f& p1, const Vector2f& p2,
                    const Circlef& circle, Vector2f* entry = nullptr,
                    Vector2f* exit = nullptr);
     
    // 3D intersections
    bool pointInAABB(const Vector3f& point, const AABBf& aabb);
    bool pointInSphere(const Vector3f& point, const Vector3f& center, float radius);
    bool aabbsIntersect(const AABBf& a, const AABBf& b);
    bool sphereSphereIntersect(const Vector3f& c1, float r1,
                               const Vector3f& c2, float r2);
    bool sphereAABBIntersect(const Vector3f& center, float radius,
                             const AABBf& aabb);
     
    // Ray intersections
    bool rayPlane(const Ray<float>& ray, const Plane<float>& plane,
                  float& t, Vector3f* intersection = nullptr);
    bool rayAABB(const Ray<float>& ray, const AABBf& aabb,
                 float& tMin, float& tMax,
                 Vector3f* entry = nullptr, Vector3f* exit = nullptr);
    bool raySphere(const Ray<float>& ray, const Vector3f& center, float radius,
                   float& t1, float& t2,
                   Vector3f* point1 = nullptr, Vector3f* point2 = nullptr);
    bool rayTriangle(const Ray<float>& ray, const Vector3f& v0,
                     const Vector3f& v1, const Vector3f& v2,
                     float& t, Vector3f* barycentric = nullptr,
                     Vector3f* normal = nullptr);
     
    // New intersection functions for geometric classes
    bool raySphere(const Ray<float>& ray, const Spheref& sphere,
                   float& t1, float& t2,
                   Vector3f* point1 = nullptr, Vector3f* point2 = nullptr);
    bool rayTriangle(const Ray<float>& ray, const Trianglef& triangle,
                     float& t, Vector3f* barycentric = nullptr,
                     Vector3f* normal = nullptr);
    bool sphereSphere(const Spheref& s1, const Spheref& s2);
    bool aabbAABB(const AABBf& a, const AABBf& b);
     
    // Frustum intersections (for camera)
    struct Frustum {
        Plane<float> planes[6]; // left, right, top, bottom, near, far
    };
     
    bool aabbInFrustum(const AABBf& aabb, const Frustum& frustum);
    bool sphereInFrustum(const Vector3f& center, float radius,
                         const Frustum& frustum);
     
    // 3D volume intersections
    bool aabbTriangle(const AABBf& aabb, const Vector3f& v0,
                      const Vector3f& v1, const Vector3f& v2);
     
    // SAT (Separating Axis Theorem) for convex polygons
    bool satTest2D(const std::vector<Vector2f>& poly1,
                   const std::vector<Vector2f>& poly2);
     
    // Intersection point calculation
    Vector3f computeIntersectionPoint(const Ray<float>& ray, float t);
     
    // Distance between objects
    float distancePointToLine(const Vector3f& point,
                              const Vector3f& lineStart,
                              const Vector3f& lineEnd);
    float distancePointToPlane(const Vector3f& point,
                               const Vector3f& planePoint,
                               const Vector3f& planeNormal);
     
    // Point classification relative to plane
    enum class PlaneSide {
        Front,
        Back,
        OnPlane
    };
     
    PlaneSide classifyPointToPlane(const Vector3f& point,
                                   const Vector3f& planePoint,
                                   const Vector3f& planeNormal);
     
    // 3D segment intersections
    bool segmentSegment(const Vector3f& p1, const Vector3f& p2,
                        const Vector3f& q1, const Vector3f& q2,
                        float& t, float& u, Vector3f* intersection = nullptr);
     
    // Ray-cylinder intersection
    bool rayCylinder(const Ray<float>& ray, const Vector3f& base,
                     const Vector3f& axis, float radius, float height,
                     float& t1, float& t2);
     
    // Ray-disk intersection
    bool rayDisk(const Ray<float>& ray, const Vector3f& center,
                 const Vector3f& normal, float radius,
                 float& t, Vector3f* intersection = nullptr);
    
    // Triangle mathematics
    Vector3f triangleNormal(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2);
    float triangleArea(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2);
    Vector3f triangleBarycentric(const Vector3f& point, const Vector3f& v0, 
                                 const Vector3f& v1, const Vector3f& v2);
};
