#include "PolynomialCurveSegment.h"
#include <cogra/exceptions/RuntimeError.h>
namespace GeoVer
{
PolynomialCurveSegment::PolynomialCurveSegment()
{}

PolynomialCurveSegment::PolynomialCurveSegment(uint32 degree)
    : m_coefficients(degree+1)
{}

PolynomialCurveSegment::PolynomialCurveSegment(const std::vector<f32vec2>& coefficients)
    : m_coefficients(coefficients)
{
    if(getDegree() > maxDegree)
    {
        throw cogra::exceptions::RuntimeError("Degree is higher than allowed");
    }

    if(getDegree() < minDegree)
    {
        throw cogra::exceptions::RuntimeError("Degree is smaller than allowed");
    }
}

const f32vec2&  PolynomialCurveSegment::operator[](size_t i) const
{
    return m_coefficients[i];
}

f32vec2&  PolynomialCurveSegment::operator[](size_t i)
{
    return m_coefficients[i];
}

 const f32vec2 & PolynomialCurveSegment::getCoefficient(size_t i) const
{
    return m_coefficients[i];
}

 f32vec2 & PolynomialCurveSegment::getCoefficient(size_t i)
{
    return m_coefficients[i];
}

uint32 PolynomialCurveSegment::getDegree() const
{
    return static_cast<uint32>(m_coefficients.size()) - 1;
}

uint32 PolynomialCurveSegment::getOrder() const
{
    return static_cast<uint32>(m_coefficients.size());
}

const std::vector<f32vec2>& PolynomialCurveSegment::getCoefficients() const
{
    return m_coefficients;
}

std::vector<f32vec2>& PolynomialCurveSegment::getCoefficients()
{
    return m_coefficients;
}

std::vector<f32vec2> PolynomialCurveSegment::sample(const uint32 nSamplePoints) const
{
    std::vector<f32vec2> sampledPoints;    
    // Assignment 1b
    const float dt = 1.0f / (nSamplePoints - 1);
    // sampledPoints.push_back(this->evaluate(0.0));
    // TODO sample nSamplePoints-2 along the curve between 0.0f < t < 1.0f
    for  (int i = 0;  i < nSamplePoints; i++)
    {
        // compute t where we want to evalate
        float t = i * dt;

        // compute sample point at t
        f32vec2 samplePoint = this->evaluate(t);

        // add sample point to vector sampledPoints
        sampledPoints.push_back(samplePoint);
    }
    //sampledPoints.push_back(this->evaluate(1.0));
    return sampledPoints;
}

}