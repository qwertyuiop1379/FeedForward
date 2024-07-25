#include <FeedForward/FeedForward.hpp>

using namespace Math;

int main(int argc, char **argv)
{
    std::vector<std::pair<Vector<float>, FVector>> data;
    for (int i = 0; i < 1000; i++)
    {
        float a = FeedForward::RandomRange(0, 10);
        std::pair<Vector<float>, FVector> point(Math::Vector<float>(1, a), Math::Vector<float>(1, a * a / 100));
        data.push_back(point);
    }

    FeedForward::Model model(1, 1, {10, 10, 10});
    for (size_t i = 0; i < 500000; i++)
    {
        const auto &point = data[i % data.size()];
        model.Train(0.01, point.first, point.second);

        if (i % 100000 == 0)
        {
            FVector test(1, 4);
            auto prediction = model.Predict(test);
            printf("[training update] prediction: 4 * 4 = %.3f\n", prediction[0] * 100);
        }
    }

    printf("\n[training complete]\n\n");

    FVector test(1, 5);
    auto prediction = model.Predict(test);
    printf("prediction: %.0f * %.0f = %.2f\n", test[0], test[0], prediction[0] * 100);

    test = FVector(1, 3);
    prediction = model.Predict(test);
    printf("prediction: %.0f * %.0f = %.2f\n", test[0], test[0], prediction[0] * 100);

    test = FVector(1, 9);
    prediction = model.Predict(test);
    printf("prediction: %.0f * %.0f = %.2f\n", test[0], test[0], prediction[0] * 100);

    test = FVector(1, 8);
    prediction = model.Predict(test);
    printf("prediction: %.0f * %.0f = %.2f\n\n", test[0], test[0], prediction[0] * 100);

    return 0;
}