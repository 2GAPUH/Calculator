#pragma once
#include "CalculatedValue.h"

class MatrixValue : public CalculatedValue
{
	float** value = nullptr;
    int rows = 0, columns = 0;

public:
    MatrixValue(std::string str);
    MatrixValue(std::string str, JsonContent& content);
    MatrixValue(float** matr, int rows, int columns);
    ~MatrixValue();

    CalculatedValue* operator+(CalculatedValue*& other) const override;
    CalculatedValue* operator-(CalculatedValue*& other) const override;
    CalculatedValue* operator*(CalculatedValue*& other) const override;
    CalculatedValue* operator/(CalculatedValue*& other) const override;
    CalculatedValue* operator^(CalculatedValue*& other) const override;
    CalculatedValue* operator-() const override;
    ExpressionType GetType() const override;
    void ConsolePrint() const override;
};

