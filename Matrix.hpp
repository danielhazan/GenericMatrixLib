//
// Created by daniel.hazan on 1/26/18.
//

#ifndef EX3NEW_MATRIX_HPP
#define EX3NEW_MATRIX_HPP

//
// Created by daniel hazan on 1/19/2018.
//



#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
#include <ostream>
#include "Complex.h"
//#include <iosream>

template<class T>
class Matrix
{

public:
    std::vector<T> vector;
    unsigned int _cols;
    unsigned int _rows;
    unsigned int size;
    typedef typename std::vector<T>::const_iterator const_iterator;
    Matrix();
    Matrix(unsigned int rows, unsigned int cols );
    Matrix(const Matrix<T>& matrix);
    Matrix(Matrix<T>&& matrix);
    Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells);
    ~Matrix();
    bool operator != (const Matrix<T>& other) const;
    bool operator == (const Matrix<T>& other) const;
    Matrix<T>&operator=(const Matrix<T>& other);
    Matrix<T>operator+(const Matrix<T>& other);
    Matrix<T>operator-(const Matrix<T>& other);
    Matrix<T>operator*(const Matrix<T>& other);
    Matrix<T> trans() const;
    bool isSquareMatrix();

    friend std::ostream& operator<<(std::ostream& os , const Matrix<T>& matrix)
    {
        for(unsigned int i  = 0; i<matrix._rows; i++)
        {
            for(unsigned int j = 0; j < matrix._cols; j++)
            {
                if(i==0) {
                    os << matrix.vector.at((i % matrix._cols) + j) << "\t";
                }
                else{
                    os << matrix.vector.at((i * matrix._cols) + j) << "\t";
                }
            }
            os<<"\n";
        }
        return os;
    }
    T& operator()(unsigned int row, unsigned int col);
    T operator()(unsigned int row, unsigned int col) const;
    const_iterator begin() const;
    const_iterator end() const;
    unsigned int   rows() const;
    unsigned int   cols() const;



};



    template <class T>
    Matrix<T>::Matrix():vector(1,0), _cols(1),_rows(1){}

    template<class T>
    Matrix<T>::Matrix(unsigned int rows, unsigned int cols ):vector(rows*cols),_cols(cols),_rows(rows), size
            (rows*cols)
    {
        if(rows<0 || cols <0)
        {
            throw std::out_of_range("there are not enough, or there are too many, items in the "
                                            "input vector");
        }
        for( unsigned int i = 0; i<_rows;i++)
        {
            for(unsigned int j= 0;j<_cols; j++)
            {
                vector.push_back(0);
            }

        }
    }
    template<class T>
    Matrix<T>::Matrix(const Matrix<T>& matrix):vector(),_cols(matrix._cols),_rows
            (matrix._cols), size(_rows*_cols)
    {
        for( unsigned int i = 0; i<_rows;i++)
        {
            for(unsigned int j= 0;j<_cols; j++)
            {

                if(i==0) {
                    vector.push_back(matrix.vector.at((i % _cols) + j));
                }
                else{
                    vector.push_back(matrix.vector.at((i * _cols) + j));
                }
            }

        }
    }
    template<class T>
    Matrix<T>::Matrix(Matrix<T>&& matrix) :vector(std::move(matrix.vector)),_cols(matrix._cols),
                                      _rows(matrix._cols), size(_rows*_cols)
    {
        /**
        for( unsigned int i = 0; i<_rows;i++)
        {
            for(unsigned int j= 0;j<_cols; j++)
            {
                vector.push_back(matrix.vector.at((i%_cols) +j));
            }

        }
        matrix.vector = nullptr;// let him dy peacefully!!
         **/
    }
    template <class T>
    Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells):vector(),
                                                                              _cols(cols),_rows
                                                                                      (rows),
                                                                              size(rows*cols)
    {
        if(cells.size()> _rows*_cols || cells.size() < _rows*_cols)
        {
            throw std::out_of_range("there are not enough, or there are too many, items in the "
                                            "input vector");
        }

        for( unsigned int i = 0; i<_rows;i++)
        {
            for(unsigned int j= 0;j<_cols; j++)
            {
               
                if(i==0) {
                    vector.push_back(cells.at((i % _cols) + j));
                }
                else{
                    vector.push_back(cells.at((i * _cols) + j));
                }
            }

        }
    }
    template<class T>
    Matrix<T>::~Matrix()
    {
        // the vector will delete hitself when object is destroyed.
        vector.clear();
    }
    template <class T>
    bool Matrix<T>::operator == (const Matrix<T>& other) const
    {

        for( unsigned int i = 0; i<_rows;i++)
        {
            for(unsigned int j= 0;j<_cols; j++)
            {
                if(i*_cols + j >other.vector.size())
                {
                    throw std::out_of_range("matrices of differrent sizes.");
                }

                if (i==0 && other.vector.at((i % _cols) + j) != this->vector.at((i % _cols) + j))
                {
                    return false;
                }
                if (i>0 && other.vector.at((i * _cols) + j) != this->vector.at((i * _cols) + j))
                {
                    return false;
                }


            }

        }
        return true;
    }
    template<class T>
    bool Matrix<T>::operator != (const Matrix<T>& other) const
    {

        for( unsigned int i = 0; i<_rows;i++)
        {
            for(unsigned int j= 0;j<_cols; j++)
            {
                if(i*_cols + j >other.vector.size()){
                    throw std::out_of_range("matrices of differrent sizes.");
                }

                if (i==0 && other.vector.at((i % _cols) + j) != this->vector.at((i % _cols) + j))
                {
                    return true;
                }
                if (i>0 && other.vector.at((i * _cols) + j) != this->vector.at((i * _cols) + j))
                {
                    return true;
                }




            }

        }
        //if we got here means the matrices are equal cord - cord
        return false;
    }

    template<class T>
    Matrix<T>&Matrix<T>::operator=(const Matrix<T>& other)
    {

        vector.clear();
        std::vector<T> newVec;
        this->vector = newVec;//??
        this->_rows = other._rows;
        this->_cols = other._cols;
        for( unsigned int i = 0; i<other._rows;i++)
        {
            for(unsigned int j= 0;j<other._cols; j++)
            {
                if(i==0) {
                    vector.push_back(other.vector.at((i % _cols) + j));
                }
                else{
                    vector.push_back(other.vector.at((i * _cols) + j));
                }
            }

        }
        if(this == &other)
        {
            throw std::invalid_argument("assign to itself!");
        }
        //this->vector = other.vector;

        //delete other;


        return *this;
    }
    template<class T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
    {
        if(other.vector.size() != vector.size())
        {
            throw std::out_of_range("matrices of differrent sizes.");
        }
        Matrix<T> temp(other);//deep copy of other


        for( unsigned int i = 0; i<other._rows;i++)
        {
            for(unsigned int j= 0;j<other._cols; j++)
            {
                if(i==0) {
                    temp.vector.at((i%_cols) + j) += vector.at((i%_cols) + j);
                }
                else{
                    temp.vector.at((i * _cols) + j) += vector.at((i*_cols) + j);
                }

            }

        }
        return temp;


    }
    template<class T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
    {
        if(other.vector.size() != vector.size())
        {
            throw std::out_of_range("matrices of differrent sizes.");
        }
        Matrix<T> temp(*this);//deep copy of other

        for( unsigned int i = 0; i<other._rows;i++)
        {
            for(unsigned int j= 0;j<other._cols; j++)
            {
                if(i==0) {
                    temp.vector.at((i%_cols) + j) -= vector.at((i%_cols) + j);
                }
                else{
                    temp.vector.at((i * _cols) + j) -= vector.at((i*_cols) + j);
                }
            }

        }
        return temp;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
    {
        if(other._rows != _cols)
        {
            throw std::out_of_range("matrices of differrent sizes.");
        }
        Matrix<T> temp(this->_rows,other._cols);//deep copy of other
        temp.vector.clear();
        Matrix<T> transmat= other.trans();

        for( unsigned int i = 0; i<this->_rows;i++)
        {
            for(unsigned int j= 0;j<other._cols; j++)
            {
                T sum =  0;
                for(unsigned int k=0;k<other._rows; k++) {


                    sum += this->vector.at((i * _cols) + k) * transmat.vector.at((j* _cols) + k);

                }
                temp.vector.push_back(sum);
            }

        }
        return temp;
    }
    template<typename T>
    Matrix<T> Matrix<T>:: trans() const
    {
        //Matrix* matrix = new Matrix(other.cols, other.rows);

        Matrix<T> temp(this->_cols , this->_rows);//deep copy
        temp.vector.clear();
        //Matrix<T> temp;//deep copy

        for( unsigned int i = 0; i<this->_cols;i++)
        {
            for(unsigned int j= 0;j<this->_rows * this->_cols; j = j + this->_cols)
            {
                temp.vector.push_back(this->vector.at(i+ j));
            }

        }
        return temp;
    }

//template <Complex T>
    template <>
    Matrix<Complex>Matrix<Complex>:: trans() const
    {
        Matrix temp(this->_cols , this->_rows);//deep copy
        temp.vector.clear();

        for( unsigned int i = 0; i<this->_cols;i++)
        {
            for(unsigned int j= 0;j<this->_rows * this->_cols; j = j + this->_cols)
            {
                temp.vector.push_back(this->vector.at(i+ j));
            }

        }
        for( unsigned int i = 0; i<_rows;i++)
        {
            for(unsigned int j= 0;j<_cols; j++)
            {
                if(i==0) {
                    temp.vector.at((i % _cols) + j) = (Complex) temp.vector.at((i % _cols) + j).conj();
                }
                else{
                    temp.vector.at((i * _cols) + j) = (Complex) temp.vector.at((i * _cols) + j).conj();
                }
            }

        }
        return temp;

    }
    template <class T>
    bool Matrix<T>::isSquareMatrix()
    {
        if (_cols == _rows)
        {
            return true;
        }
        return false;
    }
/**
    template <class T>
    std::ostream& Matrix<T>::operator<<(std::ostream& os , const Matrix<T>& matrix)
    {
        for(int i  = 0; i<matrix._rows; i++)
        {
            for(int j = 0; j < matrix._cols; j++)
            {
                os<< matrix.vector.at((i%matrix._cols) + j)<<"\t";
            }
            os<<"\n";
        }
        return os;
    }**/
    template <class T>
    T& Matrix<T>::operator()(unsigned int row, unsigned int col)
    {
        if(row>_rows || col>_cols || row<0 || col<0)
        {
            throw std::out_of_range("out of range");
        }
        return vector.at((row % (_rows+1))* _cols + col);
    }
    template <class T>
    T Matrix<T>::operator()(unsigned int row, unsigned int col) const
    {
        if(row>_rows || col>_cols || row<0 || col<0)
        {
            throw std::out_of_range("out of range");
        }
        return vector.at((row % (_rows+1))* _cols + col);
    }
    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::begin() const
    {
        return vector.cbegin();
    }
    template<class T>
    typename Matrix<T>::const_iterator Matrix<T>::end() const
    {
        return vector.cend();
    }
    template <class T>
    unsigned int  Matrix<T>:: rows() const
    {
        return _rows;
    }
    template<class T>
    unsigned int  Matrix<T>:: cols() const
    {
        return _cols;
    }














#endif //CPPEX3NEW_MATRIX_HPP



