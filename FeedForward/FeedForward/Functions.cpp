#include "Functions.hpp"

#include <random>

namespace FeedForward
{
    // Random

    float RandomRange(float min, float max)
    {
        double unscaled = (double)rand() / RAND_MAX;
        return unscaled * (max - min) + min;
    }

    // Activation functions

    template <> Math::FVector Activate<ActivationFunction::Sigmoid>(const Math::FVector &values)
    {
        Math::FVector activated(values);

        for (float &value : activated)
            value = 1 / (1 + powf(M_E, -value));

        return activated;
    }

    template <> Math::FVector Activate<ActivationFunction::ReLU>(const Math::FVector &values)
    {
        Math::FVector activated(values);

        for (float &value : activated)
            value = (value > 0) ? value : 0;

        return activated;
    }

    template <> Math::FVector ActivateDerivative<ActivationFunction::Sigmoid>(const Math::FVector &values)
    {
        Math::FVector dActivated(values);

        for (float &value : dActivated)
        {
            float exp = powf(M_E, -value);
            float plusOne = exp + 1;
            value = exp / plusOne / plusOne;
        }

        return dActivated;
    }

    template <> Math::FVector ActivateDerivative<ActivationFunction::ReLU>(const Math::FVector &values)
    {
        Math::FVector dActivated(values);
        
        for (float &value : dActivated)
            value = (value > 0) ? 1 : 0;

        return dActivated;
    }

    // Cost functions

    template <> Math::FVector Cost<CostFunction::Squared>(const Math::FVector &expected, const Math::FVector &got)
    {
        size_t count = expected.Size();
        Math::FVector cost(count);

        for (size_t i = 0; i < count; i++)
        {
            float delta = expected[i] - got[i];
            cost[i] = delta * delta / 2;
        }

        return cost;
    }

    template <> Math::FVector CostDerivative<CostFunction::Squared>(const Math::FVector &expected, const Math::FVector &got)
    {
        size_t count = expected.Size();
        Math::FVector dCost(count);

        for (size_t i = 0; i < count; i++)
            dCost[i] = 2 * (got[i] - expected[i]);

        return dCost;
    }
}