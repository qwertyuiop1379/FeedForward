#pragma once

#include <Math/Vector.hpp>

namespace FeedForward
{
    // Random

    float RandomRange(float min, float max);
    
    // Activation

    enum class ActivationFunction
    {
        Sigmoid,
        ReLU,
    };

    template <ActivationFunction> Math::FVector Activate(const Math::FVector &values);
    template <ActivationFunction> Math::FVector ActivateDerivative(const Math::FVector &values);

    // Cost

    enum class CostFunction
    {
        Squared,
    };

    template <CostFunction> Math::FVector Cost(const Math::FVector &expected, const Math::FVector &got);
    template <CostFunction> Math::FVector CostDerivative(const Math::FVector &expected, const Math::FVector &got);
}