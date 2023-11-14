#include "MonomialCurveSegment.h"
#include "LagrangeCurveSegment.h"
#include "BezierCurveSegment.h"
#include <cogra/eigen.h>
namespace GeoVer
{
MonomialCurveSegment::MonomialCurveSegment(uint32 degree)
    : PolynomialCurveSegment(degree)
{}
MonomialCurveSegment::MonomialCurveSegment(const std::vector<f32vec2>& coefficients)
    : PolynomialCurveSegment(coefficients)
{}

f32vec2 MonomialCurveSegment::evaluate(const float t) const
{
    f32vec2 result(0);        

    // Assignment 1a
    const auto n = this->getDegree();
    float t_power_i = 1.0f;
    for (int i = 0; i < n; i++)
    {
        const f32vec2 m_i = getCoefficient(i);
        result += m_i * t_power_i;
        // Use std::powf(t, i), if u want slower evaluation.
        // std::powf(t, 0) --> 1
        // std::powf(t, 1) --> t
        // std::powf(t, 2) --> t*t
        // std::powf(t, 3) --> t*t*t
        t_power_i *= t;
    }
    return result;
}

void MonomialCurveSegment::elevateDegree()
{    
    // Assignment 1f
}

void MonomialCurveSegment::reduceDegree()
{    
    // Assignment 3c
}

std::unique_ptr<PolynomialCurveSegment> MonomialCurveSegment::toMonomialCurveSegment() const
{
    return std::make_unique<MonomialCurveSegment>(getCoefficients());
}

std::unique_ptr<PolynomialCurveSegment> MonomialCurveSegment::toLagrangeCurveSegment() const
{
    // Assignment 1d
    //// Get the coefficients of the monomial curve
    //std::vector<f32vec2> monomialCoefficients = getCoefficients();
    //
    //// Calculate the corresponding Lagrange coefficients
    //std::vector<f32vec2> lagrangeCoefficients;
    //
    //for (size_t i = 0; i < monomialCoefficients.size(); ++i) {
    //    f32vec2 lagrangeCoefficient = monomialCoefficients[i] / factorial(i);
    //    lagrangeCoefficients.push_back(lagrangeCoefficient);
    //}
    //
    //// Create a LagrangeCurveSegment with the new coefficients
    return std::make_unique<LagrangeCurveSegment>(getCoefficients());
}

std::unique_ptr<PolynomialCurveSegment> MonomialCurveSegment::toBezierCurveSegment() const
{
    // Assignemt 2b
    return std::make_unique<BezierCurveSegment>(getCoefficients());
}

Eigen::MatrixXf MonomialCurveSegment::monomialBasisFunctionsToBezierBasisFunctions(uint32 degree)
{
    Eigen::MatrixXf m = Eigen::MatrixXf::Identity(degree + 1, degree + 1);
    // Assignment 2b    
    return m;
}
}