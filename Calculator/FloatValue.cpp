#include "FloatValue.h"
#include "Token.h"  

FloatValue::FloatValue(std::string str)
{
    bool validInput = false;
    while (!validInput) 
    {
        std::cout << "Enter " << str << " value: ";
        std::string input;
        std::cin >> input;

        try 
        {
            value = std::stof(input);
            validInput = true;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid input. Please enter a valid float value." << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Input out of range. Please enter a valid float value." << std::endl;
        }
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

FloatValue::FloatValue(std::string str, JsonContent& content)
{
    for (auto cont : content.variables)
    {
        if (cont.getMemberNames()[0] == str)
        {
            std::string var = cont[cont.getMemberNames()[0]].asString();
            value = std::stof(var);
            return;
        }
    }
    throw(ErrorsType::UNDEFINED_VARIABLE);
}

FloatValue::FloatValue(Token token)
{
    value = stof(token.GetValue());
}

FloatValue::FloatValue(float i) : value(i) {}

CalculatedValue* FloatValue::operator+(CalculatedValue*& other) const
{
    FloatValue* tmp = dynamic_cast<FloatValue*>(other);
    return new FloatValue(value + tmp->value);
}

CalculatedValue* FloatValue::operator-(CalculatedValue*& other) const
{
    FloatValue* tmp = dynamic_cast<FloatValue*>(other);
    return new FloatValue(value - tmp->value);
}

CalculatedValue* FloatValue::operator*(CalculatedValue*& other) const
{
    FloatValue* tmp = dynamic_cast<FloatValue*>(other);
    return new FloatValue(value * tmp->value);
}

CalculatedValue* FloatValue::operator/(CalculatedValue*& other) const
{
    FloatValue* tmp = dynamic_cast<FloatValue*>(other);
    if (tmp->value == 0)
        throw(ErrorsType::ZERO_DEVIDE);
    return new FloatValue(value / tmp->value);
}

CalculatedValue* FloatValue::operator^(CalculatedValue*& other) const
{
    float tmp = dynamic_cast<FloatValue*>(other)->GetValue();
    tmp = std::round(tmp);
    tmp = std::abs(tmp);

    float result = std::pow(value, tmp);
    if (std::isnan(result)) 
        throw(ErrorsType::POWER_OVERFLOW);
    
    return new FloatValue(result);
}

CalculatedValue* FloatValue::operator-() const
{
    return new FloatValue(-value); 
}

ExpressionType FloatValue::GetType() const
{
    return ExpressionType::FLOAT;
}

float FloatValue::GetValue()
{
    return value;
}

void FloatValue::ConsolePrint() const
{
    std::cout << value << std::endl;
}
