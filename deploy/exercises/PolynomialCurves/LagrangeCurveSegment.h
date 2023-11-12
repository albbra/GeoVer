#pragma once
#ifndef LAGRANGECURVESEGMENT_H
#define LAGRANGECURVESEGMENT_H
#include "PolynomialCurveSegment.h"
#include <cogra/eigen.h>
namespace GeoVer
{
class MonomialCurveSegment;
class BezierCurveSegment;
class LagrangeCurveSegment : public PolynomialCurveSegment
{
public:
    LagrangeCurveSegment(const std::vector<f32vec2>& coefficients);

    LagrangeCurveSegment(uint32 degree);

    virtual f32vec2 evaluate(const float t) const override;

    virtual void elevateDegree() override;

    virtual void reduceDegree() override;

    virtual std::unique_ptr<PolynomialCurveSegment> toMonomialCurveSegment() const;

    virtual std::unique_ptr<PolynomialCurveSegment> toLagrangeCurveSegment() const;

    virtual std::unique_ptr<PolynomialCurveSegment> toBezierCurveSegment() const;

    /// <summary>
    /// Computes the matrix that converts the lagrange basis functions to monomial basis functions.
    /// </summary>
    /// <param name="degree">Degree of the basis functions.</param>   
    static Eigen::MatrixXf lagrangeBasisFunctionsToMonomialBasisfunctions(uint32 degree);

};
}
#endif