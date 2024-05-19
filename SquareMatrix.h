#include <iostream>
#include "C:\Main\Kodiki\C++\Labs\2Sem\LB2-2\Sequence.h"

template <class T>
class SquareMatrix 
{
    private:
        ArraySequence<ArraySequence<T>*>* matrix; 
    public:
    // конструкторы-деструкторы
        SquareMatrix(int);
    // деструкторы
        int Get_Size();
        int Get(int, int);

    // операции
        void                Resize(int);
        
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
        ArraySequence<T>*   operator[](int);
        
        SquareMatrix<T>*    operator+(SquareMatrix<T>*); 
        void                operator+=(SquareMatrix<T>*);   
        
        template <class S>
        SquareMatrix<T>*    operator*(S);
        template <class S>
        void                operator*=(S);   
        

};

// SquareMatrix<T>
    // конструкторы-деструкторы
        template <class T>
        SquareMatrix<T>::SquareMatrix(int size):
            matrix(new ArraySequence<ArraySequence<T>*>(size))
        {
            for (int i = 0; i < size; i++)
                matrix[i] = new ArraySequence<T>(size);
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
                matrix[rowIndex][i] = matrix[rowIndex][i] * S;
            }        
        }

        template <class T>
        template <class S> 
        void SquareMatrix<T>::ScalarMultAndAdd_Row(int rowIndex1, int rowIndex2, S scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                matrix[rowIndex1][i] = matrix[rowIndex1][i] + matrix[rowIndex2][i] * S;
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
                matrix[i][columnIndex] = matrix[i][columnIndex] * S;
            }        
        }

        template <class T>
        template <class S> 
        void SquareMatrix<T>::ScalarMultAndAdd_Column(int columnIndex1, int columnIndex2, S scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                matrix[i][columnIndex1] = matrix[i][columnIndex1] + matrix[i][columnIndex2] * S;
            }        
        }

    // перегрузка операторов
        template <class T> 
        ArraySequence<T>*   SquareMatrix<T>::operator[](int row)
        {
            return matrix[row];
        }

        template <class T>
        SquareMatrix<T>*    SquareMatrix<T>::operator+(SquareMatrix<T>* addMatrix)
        {
            SquareMatrix<T>* output = new SquareMatrix<T>(Get_Size());
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    output[i][j] = this[i][j] + addMatrix[i][j];
                }
            }
            return output;
        }

        template <class T>
        void                SquareMatrix<T>::operator+=(SquareMatrix<T>* addMatrix)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    this[i][j] = this[i][j] + addMatrix[i][j];
                }
            }
        }

        template <class T> 
        template <class S>
        SquareMatrix<T>*    SquareMatrix<T>::operator*(S scalar)
        {
            SquareMatrix<T>* output = new SquareMatrix<T>(Get_Size());
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    output[i][j] = this[i][j] * scalar;
                }
            }
            return output;
        }

        template <class T> 
        template <class S>
        void                SquareMatrix<T>::operator*=(S scalar)
        {
            for (int i = 0; i < Get_Size(); i++)
            {
                for (int j = 0; j < Get_Size(); j++)
                {
                    this[i][j] = this[i][j] * scalar;
                }
            }
        }