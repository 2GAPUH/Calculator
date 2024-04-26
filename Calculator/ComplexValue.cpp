#include "ComplexValue.h"
#include "FloatValue.h"


CalculatedValue* ComplexValue::operator-() const
{
    Complex result;

    result.real = value.real * -1;
    result.imag = value.imag * -1;

    return new ComplexValue(result);
}

ExpressionType ComplexValue::GetType() const
{
    return ExpressionType::COMPLEX;
}

void ComplexValue::ConsolePrint() const
{
    std::cout << "real: " << value.real << "  imag: " << value.imag << "i";
}

Complex ComplexValue::GetValue()
{
    return value;
}

ComplexValue::ComplexValue(std::string str)
{
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "Enter " << str << " real: ";
        std::string input;
        std::cin >> input;

        try
        {
            value.real = std::stof(input);
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

    validInput = false;
    while (!validInput)
    {
        std::cout << "Enter " << str << " imag: ";
        std::string input;
        std::cin >> input;

        try
        {
            value.imag = std::stof(input);
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

ComplexValue::ComplexValue(Complex value)
{
    this->value = value;
}

ComplexValue::~ComplexValue()
{
}

CalculatedValue* ComplexValue::operator+(CalculatedValue*& other) const
{
    Complex result = value;

    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();

        result.real += tmp;

        return new ComplexValue(result);
    }
    else if (other->GetType() == ExpressionType::COMPLEX)
    {
        Complex tmp = dynamic_cast<ComplexValue*>(other)->GetValue();

        result.real += tmp.real;
        result.imag += tmp.imag;

        return new ComplexValue(result);
    }
}

CalculatedValue* ComplexValue::operator-(CalculatedValue*& other) const
{
    Complex result = value;

    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();

        result.real -= tmp;

        return new ComplexValue(result);
    }
    else if (other->GetType() == ExpressionType::COMPLEX)
    {
        Complex tmp = dynamic_cast<ComplexValue*>(other)->GetValue();

        result.real -= tmp.real;
        result.imag -= tmp.imag;

        return new ComplexValue(result);
    }
}

CalculatedValue* ComplexValue::operator*(CalculatedValue*& other) const
{
    Complex result;

    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();

        result.real = value.real * tmp;
        result.imag = value.imag * tmp;

        return new ComplexValue(result);
    }
    else if (other->GetType() == ExpressionType::COMPLEX)
    {
        Complex tmp = dynamic_cast<ComplexValue*>(other)->GetValue();

        result.real = value.real * tmp.real - value.imag * tmp.imag;
        result.imag = value.real * tmp.imag + value.imag * tmp.real;

        return new ComplexValue(result);
    }
}

CalculatedValue* ComplexValue::operator/(CalculatedValue*& other) const
{
    Complex result;

    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();
        
        if (tmp == 0)
            throw(ErrorsType::ZERO_DEVIDE);

        result.real = value.real / tmp;
        result.imag = value.imag / tmp;

        return new ComplexValue(result);
    }
    else if (other->GetType() == ExpressionType::COMPLEX)
    {
        Complex tmp = dynamic_cast<ComplexValue*>(other)->GetValue();
        float tmp2 = (tmp.imag * tmp.imag + tmp.real * tmp.real);

        if (tmp2 == 0)
            throw(ErrorsType::ZERO_DEVIDE);

        result.real = (value.real * tmp.real + value.imag * tmp.imag) / tmp2;
        result.imag = (value.imag * tmp.real - value.real * tmp.imag) / tmp2;

        return new ComplexValue(result);
    }
}

CalculatedValue* ComplexValue::operator^(CalculatedValue*& other) const
{
    Complex result;

    if (other->GetType() == ExpressionType::FLOAT)
    {
        float deg = dynamic_cast<FloatValue*>(other)->GetValue();

        float r = sqrt(value.real * value.real + value.imag * value.imag);

        float fi = std::atan(value.imag / value.real);

        result.real = pow(r, deg) * std::cos(deg * fi);
        result.imag = pow(r, deg) * std::sin(deg * fi);

        return new ComplexValue(result);
    }
    else if (other->GetType() == ExpressionType::COMPLEX)
    {
        throw(ErrorsType::COMPLEX_POWER_COMPLEX);
    }
}
