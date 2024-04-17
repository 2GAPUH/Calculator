#include "FloatValue.h"

FloatValue::FloatValue(Token* token)
{
    bool flag = true;

	while (flag)
	{
        flag = false;
		std::cout << "Enter " << token->GetValue() << " value: ";
		std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear(); // Очищаем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
            std::cout << "Invalid input. Please enter a valid float value." << std::endl;
            flag = true;
        }
	}
}

FloatValue::FloatValue(float value)
{
    this->value = value;
}

CalculatedValue* FloatValue::operator+(const CalculatedValue& other) const
{
    const FloatValue& otherFloat = dynamic_cast<const FloatValue&>(other);
    return new FloatValue(this->value + otherFloat.value);
}

CalculatedValue* FloatValue::operator-(const CalculatedValue& other) const
{
    const FloatValue& otherFloat = dynamic_cast<const FloatValue&>(other);
    return new FloatValue(this->value - otherFloat.value);
}

CalculatedValue* FloatValue::operator*(const CalculatedValue& other) const
{
    const FloatValue& otherFloat = dynamic_cast<const FloatValue&>(other);
    return new FloatValue(this->value * otherFloat.value);
}

CalculatedValue* FloatValue::operator/(const CalculatedValue& other) const
{
    const FloatValue& otherFloat = dynamic_cast<const FloatValue&>(other);
    if (otherFloat.value == 0)
        throw std::invalid_argument("zero division!");
    return new FloatValue(this->value / otherFloat.value);
}

CalculatedValue* FloatValue::operator^(const CalculatedValue& other) const
{
    const FloatValue& otherFloat = dynamic_cast<const FloatValue&>(other);
    if (std::abs(otherFloat.value) > std::log(std::numeric_limits<float>::max()) / std::log(value)) 
        throw std::invalid_argument("Overflow!");
    
    return new FloatValue(pow(this->value, otherFloat.value));
}

ExpressionType FloatValue::GetExpressionType() const
{
    return ExpressionType::FLOAT;
}
