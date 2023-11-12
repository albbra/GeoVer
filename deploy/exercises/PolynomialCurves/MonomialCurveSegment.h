#pragma once
#ifndef MONOMIALCURVESEGMENT_H
#define MONOMIALCURVESEGMENT_H
#include "PolynomialCurveSegment.h"
#include <cogra/eigen.h>
namespace GeoVer
{

class LagrangeCurveSegment;
class BezierCurveSegment;

class MonomialCurveSegment : public PolynomialCurveSegment
{
public:
    MonomialCurveSegment(uint32 degree);

    MonomialCurveSegment(const std::vector<f32vec2>& coefficients);

    virtual f32vec2 evaluate(const float t) const override;

    virtual void elevateDegree() override;

    virtual void reduceDegree() override;

    std::unique_ptr<PolynomialCurveSegment> toMonomialCurveSegment() const override;

    std::unique_ptr<PolynomialCurveSegment> toLagrangeCurveSegment() const override;

    std::unique_ptr<PolynomialCurveSegment> toBezierCurveSegment() const override;

    /// <summary>
    /// Computes the matrix that converts the monomial basis functions to bezier basis functions.
    /// </summary>
    /// <param name="degree">Degree of the basis functions.</param>   
    static Eigen::MatrixXf monomialBasisFunctionsToBezierBasisFunctions(uint32 degree);

};
}
#endif