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

CalculatedValue* FloatValue::operator+(const CalculatedValue& other) const
{
    const FloatValue& otherFloat = dynamic_cast<const FloatValue&>(other);
    return new FloatValue(this->value + otherFloat.value);
}


