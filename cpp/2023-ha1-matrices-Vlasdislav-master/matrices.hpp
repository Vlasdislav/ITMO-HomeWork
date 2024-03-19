#pragma once
 
#include <string>
#include <fstream>
 
class Matrix {
    private:
        double** matrix_;
        size_t n_;
        size_t m_;
    public:
        Matrix();
        Matrix(const size_t, const size_t=1);
        Matrix(const Matrix&);
        ~Matrix();
    public:
        double* operator[](size_t);
        Matrix& operator=(const Matrix&);
    public:
        size_t rows();
        size_t cols();
};
 
Matrix inputFromFile(const std::string&);
 
void outputInFile(const std::string&, Matrix&);
 
void add(const std::string&, const std::string&);
 
void mult(const std::string&, const std::string&);