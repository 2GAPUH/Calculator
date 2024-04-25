#include "MatrixValue.h"
#include "FloatValue.h"

ExpressionType MatrixValue::GetType() const
{
    return ExpressionType::MATRIX;
}

std::ostream& MatrixValue::operator<<(std::ostream& os) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            os << value[i][j] << "  ";
        os << std::endl;
    }

    return os;
}

MatrixValue::MatrixValue(std::string str)
{
    bool validInput = false;

    while (!validInput) 
    {
        std::cout << "Enter column count (1 <= c < 11) for " << str << " matrix: ";
        std::string input;
        std::getline(std::cin, input);
        std::stringstream ss(input);

        if (ss >> columns && columns >= 1 && columns < 11 && ss.eof()) 
            validInput = true;
        else 
            std::cout << "Invalid input. Please enter a valid integer between 1 and 10." << std::endl;
    }

    validInput = false;

    while (!validInput) 
    {
        std::cout << "Enter row count (1 <= r < 11) for " << str << " matrix: ";
        std::string input;
        std::getline(std::cin, input);
        std::stringstream ss(input);

        if (ss >> rows && rows >= 1 && rows < 11 && ss.eof()) 
            validInput = true;
        else 
            std::cout << "Invalid input. Please enter a valid integer between 1 and 10." << std::endl;
    }

    value = new float* [rows];
    for (int i = 0; i < rows; i++)
        value[i] = new float[columns];
    
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            bool validInput = false;
            while (!validInput) {
                std::cout << "Enter matrix[" << i << "][" << j << "]: ";
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);

                if (ss >> value[i][j] && ss.eof()) 
                    validInput = true;
                else
                    std::cout << "Invalid input. Please enter a valid float number." << std::endl;
            }
        }
    }
}

MatrixValue::~MatrixValue()
{
    if (value != nullptr)
    {
        for (int i = 0; i < rows; i++)
            delete value[i];

        delete value;
        value = nullptr;
    }
}

MatrixValue::MatrixValue(float** matr, int rows, int columns) 
{
    this->rows = rows;
    this->columns = columns;

    value = new float* [rows];
    for (int i = 0; i < rows; i++)
        value[i] = new float[columns];

    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < columns; j++) 
            value[i][j] = matr[i][j];
}

CalculatedValue* MatrixValue::operator+(CalculatedValue*& other) const
{
    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();
        for (int i = 0; i < rows; i++) 
            for (int j = 0; j < columns; j++)
                value[i][j] += tmp;

        return new MatrixValue(value, rows, columns);
    }
    else if (other->GetType() == ExpressionType::MATRIX)
    {
        MatrixValue* tmp = dynamic_cast<MatrixValue*>(other);
        if (tmp->rows != rows || tmp->columns != columns)
            throw(ErrorsType::INCOMPATIBLE_MATRIX_SIZES);

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                value[i][j] += tmp->value[i][j];

        return new MatrixValue(value, rows, columns);
    }
}

CalculatedValue* MatrixValue::operator-(CalculatedValue*& other) const
{
    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                value[i][j] -= tmp;

        return new MatrixValue(value, rows, columns);
    }
    else if (other->GetType() == ExpressionType::MATRIX)
    {
        MatrixValue* tmp = dynamic_cast<MatrixValue*>(other);
        if (tmp->rows != rows || tmp->columns != columns)
            throw(ErrorsType::INCOMPATIBLE_MATRIX_SIZES);

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                value[i][j] -= tmp->value[i][j];

        return new MatrixValue(value, rows, columns);
    }
}

CalculatedValue* MatrixValue::operator*(CalculatedValue*& other) const
{
    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                value[i][j] *= tmp;

        return new MatrixValue(value, rows, columns);
    }
    else if (other->GetType() == ExpressionType::MATRIX)
    {
        MatrixValue* tmp = dynamic_cast<MatrixValue*>(other);
        if (columns != tmp->rows)
            throw(ErrorsType::INCOMPATIBLE_MATRIX_SIZES);

        float** result = new float* [rows];
        for (int i = 0; i < rows; i++) 
        {
            result[i] = new float[tmp->columns];
            for (int j = 0; j < tmp->columns; j++) 
                result[i][j] = 0; 
        }

        for (int i = 0; i < rows; i++) 
            for (int j = 0; j < tmp->columns; j++) 
                for (int k = 0; k < columns; k++) 
                    result[i][j] += value[i][k] * tmp->value[k][j];

        return new MatrixValue(result, rows, tmp->columns);
    }
}

CalculatedValue* MatrixValue::operator/(CalculatedValue*& other) const
{
    if (other->GetType() == ExpressionType::FLOAT)
    {
        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();
        if (tmp == 0)
            throw(ErrorsType::ZERO_DEVIDE);

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                value[i][j] /= tmp;

        return new MatrixValue(value, rows, columns);
    }
    else if (other->GetType() == ExpressionType::MATRIX)
    {
        throw(ErrorsType::MATRIX_DIVIDE_MATRIX);
    }
}

CalculatedValue* MatrixValue::operator^(CalculatedValue*& other) const
{
    if (other->GetType() == ExpressionType::FLOAT)
    {
        int curDegree = 1;

        float tmp = dynamic_cast<FloatValue*>(other)->GetValue();
        if (columns != rows)
            throw(ErrorsType::INCOMPATIBLE_MATRIX_SIZES);

        tmp = std::round(tmp);
        tmp = std::abs(tmp);

        float** result = new float* [rows];
        for (int i = 0; i < rows; i++)
            result[i] = new float[columns];

        if (tmp == 0)
        {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                {
                    if (i == j)
                        result[i][j] = 1;
                    else
                        result[i][j] = 0;
                }
            return new MatrixValue(result, rows, columns);
        }
        else
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                     result[i][j] = value[i][j];

        while(curDegree < tmp)
        {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    for (int k = 0; k < columns; k++)
                        result[i][j] += value[i][k] * value[k][j];
        }

        return new MatrixValue(result, rows, columns);
    }
    else if (other->GetType() == ExpressionType::MATRIX)
    {
        throw(ErrorsType::MATRIX_POWER_MATRIX);
    }
}

CalculatedValue* MatrixValue::operator-() const
{
    return nullptr;
}

/*
Matrix + float
Complex + float
float + float
Matrix + Matrix
Complex + Complex
*/
