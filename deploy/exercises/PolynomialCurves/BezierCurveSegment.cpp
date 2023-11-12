#include "BezierCurveSegment.h"
#include "MonomialCurveSegment.h"
#include "LagrangeCurveSegment.h"
#include <cogra/exceptions/RuntimeError.h>
namespace
{
static const float32 b0[] = { 1.0f };
static const float32 b1[] = { 1.0f, 1.0f };
static const float32 b2[] = { 1.0f, 2.0f, 1.0f };
static const float32 b3[] = { 1.0f, 3.0f, 3.0f, 1.0f };
static const float32 b4[] = { 1.0f, 4.0f, 6.0f, 4.0f, 1.0f };
static const float32 b5[] = { 1.0f, 5.0f, 10.0f, 10.0f, 5.0f, 1.0f };
static const float32 b6[] = { 1.0f, 6.0f, 15.0f, 20.0f, 15.0f, 6.0f, 1.0f };
static const float32 b7[] = { 1.0f, 7.0f, 21.0f, 35.0f, 35.0f, 21.0f, 7.0f, 1.0f };
static const float32 b8[] = { 1.0f, 8.0f, 28.0f, 56.0f, 70.0f, 56.0f, 28.0f, 8.0f, 1.0f };
static const float32 b9[] = { 1.0f, 9.0f, 36.0f, 84.0f, 126.0f, 126.0f, 84.0f, 36.0f, 9.0f, 1.0f };
static const float32 b10[] = { 1.0f, 10.0f, 45.0f, 120.0, 210.0f, 252.0f, 210.0f, 120.0f, 45.0f, 10.0f, 1.0f };
static const float32* binomialCoefficients[] = {b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10};
}

namespace GeoVer
{
BezierCurveSegment::BezierCurveSegment(const std::vector<f32vec2>& coefficients)
    : PolynomialCurveSegment(coefficients)
{}

BezierCurveSegment::BezierCurveSegment(uint32 degree)
    : PolynomialCurveSegment(degree)
{}

f32vec2 BezierCurveSegment::evaluate(const float t) const
{    
    // Assignment 2a
    return f32vec2(0, 0);
}

void BezierCurveSegment::elevateDegree()
{
    // Assignment 3a
    if(getDegree() + 1 > maxDegree)
    {
        throw cogra::exceptions::RuntimeError("Degree is higher than allowed");
    }
}

void BezierCurveSegment::reduceDegree()
{
     // Assignment 3b
}

float32 BezierCurveSegment::binomial(uint32 i, uint32 j)
{
    return binomialCoefficients[i][j];
}

Eigen::MatrixXf BezierCurveSegment::degreeElevationMatrix(uint32 sourceDegree)
{
    Eigen::MatrixXf m = Eigen::MatrixXf::Zero(sourceDegree + 2, sourceDegree + 1);
    // Assignment 3b
    return m;
}

std::unique_ptr<PolynomialCurveSegment> BezierCurveSegment::toMonomialCurveSegment() const
{    
    // Assignment 2b
    return std::make_unique<MonomialCurveSegment>(getCoefficients());
}

std::unique_ptr<PolynomialCurveSegment> BezierCurveSegment::toLagrangeCurveSegment() const
{    
    // Assignment 2c
    return std::make_unique<LagrangeCurveSegment>(getCoefficients());
}

std::unique_ptr<PolynomialCurveSegment> BezierCurveSegment::toBezierCurveSegment() const
{
    return std::make_unique<BezierCurveSegment>(getCoefficients());
}
}
