#include <iostream>
#include "C:\Main\Kodiki\C++\Labs\2Sem\LW_2sem-2\Sequence.h"

template <class T>
class SquareMatrix 
{
    public:
        ArraySequence<ArraySequence<T>*>* matrix; 
    
    // конструкторы-деструкторы
        SquareMatrix();
        SquareMatrix(int);
        ~SquareMatrix();

    // деконструкторы
        int Get_Size();
        int Get(int, int);

    // операции
        void                Resize(int);
        void                Set(T, int, int);


        void                Swap_Rows(int, int);
        template <class S>
        void                ScalarMult_Row(int, S);
        template <class S>
        void                ScalarMultAndAdd_Row(int, int, S);
        
        void                Swap_Columns(int, int);
        template <class S>
        void                ScalarMult_Column(int, S);
        template <class S>
        void                ScalarMultAndAdd_Column(int, int,  S);
        
    // перегрузка операторов
        ArraySequence<T>&   operator[](int);
        
        SquareMatrix<T>&    operator+( SquareMatrix<T>); 
        void                operator+=( SquareMatrix<T>);   
        
        SquareMatrix<T>&    operator*( SquareMatrix<T>);
        void                operator*=( SquareMatrix<T>);   

        SquareMatrix<T>&    operator*( float );
        void                operator*=( float );   
        

};

// SquareMatrix<T>
    // конструкторы-деструкторы
        template <class T>
        SquareMatrix<T>::SquareMatrix():
            matrix(new ArraySequence<ArraySequence<T>*>(2))
        {  for (int i = 0; i < 2; i++)
                matrix->Set(i, new ArraySequence<T>(2));
        }

        template <class T>
        SquareMatrix<T>::SquareMatrix(int size):
            matrix(new ArraySequence<ArraySequence<T>*>(size))
        {
            for (int i = 0; i < size; i++)
                matrix->Set(i, new ArraySequence<T>(size));
        }

        template <class T>
        SquareMatrix<T>::~SquareMatrix()
        {
            delete matrix;
        }
    
    // деструкторы
        template <class T>
        int SquareMatrix<T>::Get_Size()
        {
            return matrix->GetSize();
        }
        
        template <class T>
        int SquareMatrix<T>::Get(int rowIndex, int colIndex)
        {
            return matrix->Get(rowIndex)->Get(colIndex);
        }
    
    // операции
        template <class T> 
        void SquareMatrix<T>::Set(T value, int rowIndex, int columnIndex)
        {
            matrix->Get(rowIndex)->Set(columnIndex, value);
        }


        template <class T> 
        void SquareMatrix<T>::Resize(int newSize)
        {
            matrix->Resize(newSize);
            for (int i; i < newSize; i++)
                matrix[i].Resize(newSize);
        }

        template <class T>
        void SquareMatrix<T>::Swap_Rows(int rowIndex1, int rowIndex2)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                T buffer = matrix[rowIndex1][i];
                matrix[rowIndex1][i] = matrix[rowIndex2][i];
                matrix[rowIndex2][i] = buffer;
            }
        }

        template <class T>
        template <class S> 
        void SquareMatrix<T>::ScalarMult_Row(int rowIndex, S scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                matrix[rowIndex][i] = matrix[rowIndex][i] * scalar;
            }        
        }

        template <class T>
        template <class S> 
        void SquareMatrix<T>::ScalarMultAndAdd_Row(int rowIndex1, int rowIndex2, S scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                matrix[rowIndex1][i] = matrix[rowIndex1][i] + matrix[rowIndex2][i] * scalar;
            }        
        }

        template <class T>
        void SquareMatrix<T>::Swap_Columns(int columnIndex1, int columnIndex2)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                T buffer = matrix[i][columnIndex1];
                matrix[i][columnIndex1] = matrix[i][columnIndex2];
                matrix[i][columnIndex2] = buffer;
            }
        }

        template <class T>
        template <class S> 
        void SquareMatrix<T>::ScalarMult_Column(int columnIndex, S scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                matrix[i][columnIndex] = matrix[i][columnIndex] * scalar;
            }        
        }

        template <class T>
        template <class S> 
        void SquareMatrix<T>::ScalarMultAndAdd_Column(int columnIndex1, int columnIndex2, S scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                matrix[i][columnIndex1] = matrix[i][columnIndex1] + matrix[i][columnIndex2] * scalar;
            }        
        }

    // перегрузка операторов
        template <class T> 
        ArraySequence<T>&   SquareMatrix<T>::operator[](int row)
        {
            return *((*matrix)[row]);
        }

        template <class T>
        SquareMatrix<T>&     SquareMatrix<T>::operator+( SquareMatrix<T> addMatrix)
        {
            SquareMatrix<T>& output = * new SquareMatrix<T>(Get_Size());
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    output[i][j] = (*this)[i][j] + addMatrix[i][j];
                }
            }
            return output;
        }

        template <class T>
        void                SquareMatrix<T>::operator+=(SquareMatrix<T> addMatrix)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    (*this)[i][j] += addMatrix[i][j];
                }
            }
        }

        template <class T> 
        SquareMatrix<T>&    SquareMatrix<T>::operator*( float scalar)
        {
            SquareMatrix<T>& output = * new SquareMatrix<T>(Get_Size());
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    output[i][j] = (*this)[i][j] * scalar;
                }
            }
            return output;
        }

        template <class T> 
        void                SquareMatrix<T>::operator*=( float scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    (*this)[i][j] *= scalar;
                }
            }
        }

        template <class T> 
        void                SquareMatrix<T>::operator*=( SquareMatrix<T> matr2)
        {
            SquareMatrix<T> output = SquareMatrix<T>(Get_Size());
            for (int row = 0; row < Get_Size(); row++)
                for (int column = 0; column < Get_Size(); column++)
                {
                    output[row][column] = T();
                    for (int i = 0; i < Get_Size(); i++)
                        output[row][column] += ((*this)[row][i] + matr2[i][column]);
                }
            *this = output;
        }
        
        template <class T> 
        SquareMatrix<T>&    SquareMatrix<T>::operator*( SquareMatrix<T> matr2)
        {
            SquareMatrix<T>& output = * new SquareMatrix<T>(Get_Size());
            for (int row = 0; row < Get_Size(); row++)
                for (int column = 0; column < Get_Size(); column++)
                {
                    output[row][column] = T();
                    for (int i = 0; i < Get_Size(); i++)
                        output[row][column] += ((*this)[row][i] + matr2[i][column]);
                }
            return output;
        }
