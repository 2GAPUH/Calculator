#include "MatrixValue.h"
#include "FloatValue.h"

ExpressionType MatrixValue::GetType() const
{
    return ExpressionType::MATRIX;
}

void MatrixValue::ConsolePrint() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            std::cout << value[i][j] << " ";
        std::cout << std::endl;
    }
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

MatrixValue::MatrixValue(std::string str, JsonContent& content)
{
    for (auto cont : content.variables)
    {
        if (!cont.isMember("name"))
            throw(ErrorsType::UNNAMED_FIELD);
        if (cont["name"].asString() == str)
        {
            if (!cont.isMember("rows") || !cont.isMember("columns"))
                throw(ErrorsType::FIELD_ABSENCE);

            rows = std::stof(cont["rows"].asString());
            columns = std::stof(cont["columns"].asString());

            if (rows < 1 || rows > 10 || columns > 10 || columns < 1)
                throw(ErrorsType::INVALID_MATRIX_SIZE);

            if (!cont.isMember("num"))
                throw(ErrorsType::FIELD_ABSENCE);
 
            value = new float* [rows];
            for (int i = 0; i < rows; i++)
                value[i] = new float[columns];

            Json::Value num = cont["num"];
            int i = 0, j = 0;

            for (auto tmp : num)
            {
                value[i][j] = tmp.asFloat();
                
                j++;
                if (j >= columns)
                {
                    j = 0;
                    i++;
                }
                if (i >= rows)
                    return;
            }

            throw(ErrorsType::MATRIX_INIT_ERROR);
        }
    }
    throw(ErrorsType::UNDEFINED_VARIABLE);
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

        MatrixValue * tmp3 = new MatrixValue(result, rows, tmp->columns);
        for (int i = 0; i < rows; i++)
            delete result[i];
        delete result;
        return tmp3;
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

        float** tmpResult = new float* [rows];
        for (int i = 0; i < rows; i++)
            tmpResult[i] = new float[columns];

        if (tmp == 0)
        {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                {
                    if (i == j)
                        tmpResult[i][j] = 1;
                    else
                        tmpResult[i][j] = 0;
                }

            MatrixValue* tmp3 = new MatrixValue(tmpResult, rows, columns);
            
            for (int i = 0; i < rows; i++)
                delete tmpResult[i];
            delete tmpResult;
            
            return tmp3;
        }
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                tmpResult[i][j] = value[i][j];

        float** result = new float* [rows];
        for (int i = 0; i < rows; i++)
            result[i] = new float[columns];
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result[i][j] = 0;

        while(curDegree < tmp)
        {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < rows; j++)
                    for (int k = 0; k < columns; k++)
                        result[i][j] += tmpResult[i][k] * value[k][j];
            curDegree++;

            if(curDegree < tmp)
            {
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < columns; j++)
                    {
                        tmpResult[i][j] = result[i][j];
                        result[i][j] = 0;
                    }
            }
        }

        MatrixValue* tmp3 = new MatrixValue(result, rows, columns);

        for (int i = 0; i < rows; i++)
        {
            delete tmpResult[i];
            delete result[i];
        }
        delete tmpResult;
        delete result;

        return tmp3;
    }
    else if (other->GetType() == ExpressionType::MATRIX)
    {
        throw(ErrorsType::MATRIX_POWER_MATRIX);
    }
}

CalculatedValue* MatrixValue::operator-() const
{
    float** result = new float* [rows];
    for (int i = 0; i < rows; i++)
        result[i] = new float[columns];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result[i][j] = -value[i][j];

    MatrixValue* tmp3 = new MatrixValue(result, rows, columns);
    for (int i = 0; i < rows; i++)
        delete result[i];
    delete result;

    return tmp3;
}

/*
Matrix + float
Complex + float
float + float
Matrix + Matrix
Complex + Complex
*/
