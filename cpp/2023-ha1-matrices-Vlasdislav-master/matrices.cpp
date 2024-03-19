#include <iostream>
 
#include "matrices.hpp"
 
Matrix::Matrix() : matrix_(nullptr), n_(0), m_(0) {}
 
Matrix::Matrix(const size_t n, const size_t m)
                : matrix_(new double*[n]), n_(n), m_(m) {
    matrix_[0] = new double[n * m]{};
    for (size_t i = 1; i < n; ++i) {
        matrix_[i] = matrix_[i - 1] + m;
    }
}
 
Matrix::Matrix(const Matrix& other)
    : n_(other.n_), m_(other.m_) {
    size_t n = n_;
    size_t m = m_;
    matrix_ = new double*[n];
    matrix_[0] = new double[n * m]{};
    for (size_t i = 1; i < n; ++i) {
        matrix_[i] = matrix_[i - 1] + m;
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}
 
Matrix::~Matrix() {
    delete[] matrix_[0];
    delete[] matrix_;
}
 
double* Matrix::operator[](size_t i) {
    return matrix_[i];
}
 
Matrix &Matrix::operator=(const Matrix &other) {
    if (this == &other) {
      return *this;
    }
    delete[] matrix_[0];
    delete[] matrix_;
    size_t n = other.n_;
    size_t m = other.m_;
    matrix_ = new double*[n];
    matrix_[0] = new double[n * m]{};
    for (size_t i = 1; i < n; ++i) {
        matrix_[i] = matrix_[i - 1] + m;
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
    return *this;
}
 
size_t Matrix::rows() {
    return n_;
}
 
size_t Matrix::cols() {
    return m_;
}
 
Matrix inputFromFile(const std::string& file) {
    std::ifstream in(file);
    if (in.is_open()) {
        size_t n, m;
        in >> n >> m;
        Matrix res(n, m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                in >> res[i][j];
            }
        }
        return res;
    } else {
        std::cerr << "error-inFile-isn\'t-open\n";
        exit(1);
    }
    return Matrix();
}
 
void outputInFile(const std::string& file, Matrix &matrix) {
    std::ofstream out(file);
    if (out.is_open()) {
        size_t n = matrix.rows();
        size_t m = matrix.cols();
        out << n << ' ' << m << std::endl;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                out << matrix[i][j] << ' ';
            }
            out << std::endl;
        }
    } else {
        std::cerr << "error-outFile-isn\'t-open\n";
        exit(1);
    }
}
 
// Сумма складывается в матрицу B
void add(const std::string &fileA,
          const std::string &fileB) {
    Matrix A = inputFromFile(fileA);
    Matrix B = inputFromFile(fileB);
    size_t n = B.rows();
    size_t m = B.cols();
    if (n == A.rows() && m == A.cols()) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                B[i][j] += A[i][j];
            }
        }
        outputInFile(fileA, B);
    } else {
        std::cerr << "error-add-size\n";
        exit(1);
    }
}
 
// Произведение складывается в матрицу res
void mult(const std::string &fileA,
          const std::string &fileB) {
    Matrix A = inputFromFile(fileA);
    Matrix B = inputFromFile(fileB);
    size_t rows_1 = A.rows();
    size_t cols_1 = A.cols();
    size_t rows_2 = B.rows();
    size_t cols_2 = B.cols();
    if (cols_1 == rows_2) {
        Matrix res(rows_1, cols_2);
        for (size_t i = 0; i < rows_1; ++i) {
            for (size_t j = 0; j < cols_2; ++j) {
                for (size_t k = 0; k < cols_1; ++k) {
                    res[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        outputInFile(fileA, res);
    } else {
        std::cerr << "error-mult-size\n";
        exit(1);
    }
}