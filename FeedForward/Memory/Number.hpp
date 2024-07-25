#pragma once

namespace Memory
{
    class Number : public Object
    {
        private:
            bool isFixedPoint;
            union {
                long long i;
                double d;
            } value;

            void InitInteger(long long i)
            {
                this->isFixedPoint = true;
                this->value.i = i;
            }

            void InitFloat(double d)
            {
                this->isFixedPoint = false;
                this->value.d = d;
            }

        public:
            Number(bool on) { this->InitInteger(on); }
            Number(int i) { this->InitInteger(i); }
            Number(unsigned int i) { this->InitInteger(i); }
            Number(long i) { this->InitInteger(i); }
            Number(unsigned long i) { this->InitInteger(i); }
            Number(long long i) { this->InitInteger(i); }
            Number(unsigned long long i) { this->InitInteger(i); }

            Number(float d) { this->InitFloat(d); }
            Number(double d) { this->InitFloat(d); }

            // Getters
            long long GetIntegerValue() { return this->isFixedPoint ? this->value.i : this->value.d; }
            unsigned long long GetUnsignedIntegerValue() { return this->isFixedPoint ? this->value.i : this->value.d; }
            long double GetFloatValue() { return this->isFixedPoint ? this->value.i : this->value.d; }
            
            template <typename T> T GetValue();
            template <> bool GetValue() { return this->GetUnsignedIntegerValue(); }
            template <> int GetValue() { return this->GetIntegerValue(); }
            template <> unsigned int GetValue() { return this->GetIntegerValue(); }
            template <> long GetValue() { return this->GetIntegerValue(); }
            template <> unsigned long GetValue() { return this->GetIntegerValue(); }
            template <> long long GetValue() { return this->GetIntegerValue(); }
            template <> unsigned long long GetValue() { return this->GetIntegerValue(); }
            template <> float GetValue() { return this->GetFloatValue(); }
            template <> double GetValue() { return this->GetFloatValue(); }
    };
}