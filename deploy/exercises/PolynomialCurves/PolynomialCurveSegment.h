#pragma once 
#ifndef POLYNOMIALCURVESEGMENT_H
#define POLYNOMIALCURVESEGMENT_H

#include <cogra/types.h>
#include <vector>
#include <memory>

using namespace cogra;

namespace GeoVer
{
/// <summary>
/// Base class for Polynomial curve segments.
/// </summary>
class PolynomialCurveSegment
{
public:
    /// <summary>
    /// Minimal degree allowed for the polynomial curve.
    /// </summary>
    static constexpr size_t minDegree = 0;

    /// <summary>
    /// Maximal degree allowed for the polynomial curve.
    /// </summary>
    static constexpr size_t maxDegree = 10;

    /// <summary>
    /// Creates an empty polynomial curve.
    /// </summary>
    PolynomialCurveSegment();

    /// <summary>
    /// Creates a polynomial curve with all control points set to zero.
    /// </summary>
    /// <param name="degree">Degree of the curve.</param>
    PolynomialCurveSegment(uint32 degree);

    /// <summary>
    /// Creates a polynomial curve from a set of coefficients.
    /// </summary>
    /// <param name="coefficients">Coefficients of the polynomial curve.</param>
    PolynomialCurveSegment(const std::vector<f32vec2>& coefficients);

    /// <summary>
    /// Returns the ith coefficient for reading. 
    /// </summary>
    /// <param name="i">Zero-based index.</param>    
    const f32vec2& operator[](size_t i) const;

    /// <summary>
    /// Returns the ith coefficient for writing.    
    /// </summary>
    /// <param name="i">Zero-based index.</param>    
    f32vec2& operator[](size_t i);

    /// <summary>
    /// Returns the ith coefficient for reading. 
    /// </summary>
    /// <param name="i">Zero-based index.</param>    
    const f32vec2& getCoefficient(size_t i) const;

    /// /// <summary>
    /// Returns the ith coefficient for writing. 
    /// </summary>
    /// <param name="i">Zero-based index.</param>    
    f32vec2& getCoefficient(size_t i);

    /// <summary>
    /// Returns the degree of the curve.
    /// </summary>
    uint32 getDegree() const;

    /// <summary>
    /// Returns the order (i.e., the number of coefficients) of the curve.
    /// </summary>
    uint32 getOrder() const;

    /// <summary>
    /// Evaluates the curve at the parameter t.
    /// 
    /// Override this function to implemenet a specific curve type.
    /// </summary>
    /// <param name="t">Parameter at which the curve is evaluated</param>
    virtual f32vec2 evaluate(const float32 t) const = 0;

    /// <summary>
    /// Samples the parameter domain of the curve uniformly from 0 to 1.
    /// </summary>
    /// <param name="nSamplePoints">The number of sample points the curve shall be sampled with.</param>
    /// <returns>A set of points.</returns>
    std::vector<f32vec2> sample(const uint32 nSamplePoints) const;

    /// <summary>
    /// Elevates the degree by one.
    /// </summary>
    virtual void elevateDegree() = 0;

    /// <summary>
    ///  Reduces the degree by one.
    /// </summary>
    virtual void reduceDegree() = 0;

    /// <summary>
    /// Returns the coefficients as an array for reading.
    /// </summary>    
    const std::vector<f32vec2>& getCoefficients() const;

    /// <summary>
    /// Returns the coefficients as an array for writing.
    /// </summary>    
    std::vector<f32vec2>& getCoefficients();

    /// <summary>
    /// Converts the curve to a MonomialCurveSegment.
    /// 
    /// Override this function to adjust to the specific curve type.
    /// </summary>
    virtual std::unique_ptr<PolynomialCurveSegment> toMonomialCurveSegment() const = 0;

    /// <summary>
    /// Converts the curve to a LagrangeCurveSegment.
    /// 
    /// Override this function to adjust to the specific curve type.
    /// </summary>
    virtual std::unique_ptr<PolynomialCurveSegment> toLagrangeCurveSegment() const = 0;

    /// <summary>
    /// Converts the curve to a BezierCurveSegment.
    /// 
    /// Override this function to adjust to the specific curve type.
    /// </summary>
    virtual std::unique_ptr<PolynomialCurveSegment> toBezierCurveSegment() const = 0;

private:
    std::vector<f32vec2>        m_coefficients;
};
}
#endif