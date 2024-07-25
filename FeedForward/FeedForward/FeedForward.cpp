#include "FeedForward.hpp"
#include "Functions.hpp"

#define ACTIVATION ActivationFunction::Sigmoid
#define COST CostFunction::Squared

using namespace Math;

namespace FeedForward
{
    // Layer

    Layer::Layer(size_t inputs, size_t outputs)
        : weights(outputs, inputs), biases(outputs)
    {
        for (size_t i = 0; i < inputs * outputs; i++)
            weights[i] = RandomRange(-1, 1);
        for (size_t i = 0; i < outputs; i++)
            biases[i] = RandomRange(-1, 1);
    }

    Math::FVector Layer::Propogate(const FVector &input) const
    {
        Math::FVector values = input;

        values = this->weights * values;
        size_t count = values.Size();

        for (size_t i = 0; i < count; i++)
            values[i] += this->biases[i];

        return values;
    }

    // Model

    Model::Model(size_t inputs, size_t outputs, const std::vector<size_t> &hiddenLayerSizes)
    {
        srand(time(nullptr));
        
        size_t lastSize = inputs;

        for (size_t layerSize : hiddenLayerSizes)
        {
            Layer layer(lastSize, layerSize);
            this->layers.push_back(layer);
            lastSize = layerSize;
        }

        Layer output(lastSize, outputs);
        this->layers.push_back(output);
    }

    Math::FVector Model::Predict(const FVector &input) const
    {
        Math::FVector values = input;
        for (const Layer &layer : this->layers)
        {
            values = layer.Propogate(values);
            values = Activate<ACTIVATION>(values);
        }

        return values;
    }

    void Model::Train(float learnRate, const FVector &input, const FVector &expected)
    {
        std::vector<FVector> nodeValuesArray;
        std::vector<FVector> activationDerivativeValuesArray;
        std::vector<FVector> activationValuesArray;

        FVector prediction = input;
        for (const Layer &layer : this->layers)
        {
            prediction = layer.Propogate(prediction);
            nodeValuesArray.push_back(prediction);

            activationDerivativeValuesArray.push_back(ActivateDerivative<ACTIVATION>(prediction));

            prediction = Activate<ACTIVATION>(prediction);
            activationValuesArray.push_back(prediction);
        }

        FVector costDerivateValues = CostDerivative<COST>(expected, prediction);
        FVector localGradient(1);

        size_t count = this->layers.size();
        for (size_t forwardIndex = 0; forwardIndex < count; forwardIndex++)
        {
            size_t i = count - forwardIndex - 1;
            Layer &layer = this->layers[i];

            const FVector &activationDerivativeValues = activationDerivativeValuesArray[i];

            if (i == count - 1)
                localGradient = activationDerivativeValues * costDerivateValues;
            else
                localGradient = activationDerivativeValues * (layers[i + 1].weights.Transpose() * localGradient);

            FVector previousLayerActivationValues = (i == 0) ? input : activationValuesArray[i - 1];
            Matrix<float> weightGradient = Matrix<float>(localGradient) * Matrix<float>(previousLayerActivationValues).Transpose();

            layer.weights -= weightGradient * learnRate;
            layer.biases -= localGradient * learnRate;
        }
    }
}