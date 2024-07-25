#pragma once

#include <Math/Math.hpp>
#include <FeedForward/Functions.hpp>

namespace FeedForward
{
    // Layer

    class Layer
    {
        public:
            Math::Matrix<float> weights;
            Math::FVector biases;

            Layer(size_t inputs, size_t outputs);
            Math::FVector Propogate(const Math::FVector &input) const;
    };

    // Model

    class Model
    {
        private:
            std::vector<Layer> layers;

        public:
            Model(size_t inputs, size_t outputs, const std::vector<size_t> &hiddenLayerSizes);
            Math::FVector Predict(const Math::FVector &input) const;
            void Train(float learnRate, const Math::FVector &input, const Math::FVector &expected);
    };
}