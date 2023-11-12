#pragma once
#ifndef BEZIERCURVESEGMENT_H
#define BEZIERCURVESEGMENT_H
#include "PolynomialCurveSegment.h"
#include <cogra/eigen.h>
namespace GeoVer
{
class MonomialCurveSegment;
class LagrangeCurveSegment;

class BezierCurveSegment : public PolynomialCurveSegment
{
public:
    BezierCurveSegment(const std::vector<f32vec2>& coefficients);

    BezierCurveSegment(uint32 degree);

    virtual f32vec2 evaluate(const float t) const override;

    virtual void elevateDegree() override;

    virtual void reduceDegree() override;

    std::unique_ptr<PolynomialCurveSegment> toMonomialCurveSegment() const override;

    std::unique_ptr<PolynomialCurveSegment> toLagrangeCurveSegment() const override;

    std::unique_ptr<PolynomialCurveSegment> toBezierCurveSegment() const override;

    static float32 binomial(uint32 i, uint32 j);    

    /// <summary>
    /// Compute the degree elevation matrix that increses the degree from source degree to target degree.
    /// </summary>
    /// <param name="sourceDegree">degree of the original curve.</param>
    static Eigen::MatrixXf degreeElevationMatrix(uint32 sourceDegree);
};
}
#endif