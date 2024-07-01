#include <iostream>
#include "C:\Main\Kodiki\C++\Labs\2Sem\LB2-2\Sequence.h"

using namespace std;

template <class T>
class Polynomial
{
    public:
        ArraySequence<T>* polynom;
    
    // конструкторы-деструкторы
        Polynomial();
        Polynomial(int);
        Polynomial(Polynomial<T> &);
        Polynomial(ArraySequence<T>*);
        ~Polynomial();
    // деконструкторы
        int Get_Size();
        T   Get(int);
    // oперации
        void Set(T, int);
        void Resize(int); 
        T EvaluateAtPoint(T);
        Polynomial<T>       Compose(Polynomial<T> &);
    // перегрузка операторов
        Polynomial<T>       operator+(Polynomial<T> &); 
        Polynomial<T>       operator*(Polynomial<T> &);
        template <class S>
        Polynomial<T>       operator*(S &);


        void                operator+=(Polynomial<T> &);   
        void                operator*=(Polynomial<T> &);        
        template <class S>
        void                operator*=(S &); 

        T&                  operator[](int);
};


// Polynomial<T>
    // конструкторы-деструкторы
    template <class T>
    Polynomial<T>::Polynomial():
        polynom(nullptr)
    { }
    
    template <class T>
    Polynomial<T>::Polynomial(int size):
        polynom(new ArraySequence<T>(size))
    { }
    
    template <class T>
    Polynomial<T>::Polynomial(ArraySequence<T>* arr):
        polynom(arr)
    { }

    template <class T>
    Polynomial<T>::Polynomial(Polynomial<T> & poly):
        polynom(new ArraySequence<T>(poly.Get_Size()))
    {
        for (int i = 0; i < Get_Size(); i++)
            polynom->Set(i, poly.Get(i));
    }
    template <class T>
    Polynomial<T>::~Polynomial()
    { 
        delete polynom;
    }

    // деконструкторы
    template <class T>
    int Polynomial<T>::Get_Size()
    {
        if (polynom == nullptr)
            return 0;
        return polynom->GetSize();
    }

    template <class T>
    T Polynomial<T>::Get(int index)
    { 
        return polynom->Get(index);
    }

    // операции
    template <class T>
    void Polynomial<T>::Set(T value, int index)
    {
        polynom->Set(index, value);
    }

    template <class T>
    void Polynomial<T>::Resize(int newSize)
    {
        polynom->Resize(newSize);
    }

    template <class T>
    T Polynomial<T>::EvaluateAtPoint(T point)
    {
        T totalSum(Get(0));
        T x = point;
        for (int i = 1; i < Get_Size(); i++)
        {
            x = point;

            for (int j = 1; j < i; j++)
                x *= point;
            totalSum += (Get(i) * x);
        }
        return totalSum;
    }  

    template <typename T>
    Polynomial<T> Polynomial<T>::Compose(Polynomial<T>& gPoly)
    {
        if (Get_Size() == 0 || gPoly.Get_Size() == 0)
        {
            return Polynomial<T>(0);
        }
        Polynomial<T>& output = * new Polynomial<T>((Get_Size() - 1)*(gPoly.Get_Size() - 1) + 1);
        output.Set(Get(0), 0);
        Polynomial<T> buffer(gPoly); 
        Polynomial<T> bufferForGet(1); 
        Polynomial<T> bufferForMult; 
        
        for (int i = 1; i < Get_Size(); i++)
        {
            if (i != 1)
                buffer *= gPoly;
            bufferForGet.Set(Get(i), 0);
            bufferForMult = bufferForGet * buffer;
            output += bufferForMult;
        }
        return output;
    }

    // перегрузка операторов
    template <class T>
    Polynomial<T>      Polynomial<T>::operator+( Polynomial<T> & poly2)
    {
        int i = 0;
        Polynomial<T> & output = * new Polynomial<T>(max(Get_Size(), poly2.Get_Size()));
        for (i; i < min(Get_Size(), poly2.Get_Size()); i++)
            output.Set(Get(i) + poly2.Get(i), i);
        if (Get_Size() > poly2.Get_Size())
            for (i; i < max(Get_Size(), poly2.Get_Size()); i++)
                output.Set(Get(i), i);
        else
            for (i; i < max(Get_Size(), poly2.Get_Size()); i++)
                output.Set(poly2.Get(i), i); 
        return output;   
    }
    
    template <class T> 
    Polynomial<T>      Polynomial<T>::operator*( Polynomial<T> & poly2)
    {
        if (Get_Size() == 0 || poly2.Get_Size() == 0)
            return * new Polynomial<T>();
        Polynomial<T>& output = * new Polynomial<T>(Get_Size() + poly2.Get_Size() - 1);
        ArraySequence<bool> isFirst(output.Get_Size());
        for (int i = 0; i < output.Get_Size(); i++)
            isFirst[i] = true; 
        for (int i = 0; i < Get_Size(); i++)
        {
            for (int j = 0; j < poly2.Get_Size(); j++)
            {
                if (isFirst[i+j])
                {
                    output[i+j] = Get(i)*poly2.Get(j);
                    isFirst[i+j] = false;
                }     
                else
                    output[i+j] += Get(i)*poly2.Get(j);
            }
        }
        return output;
    }
    
    template <class T> 
    template <class S>
    Polynomial<T>      Polynomial<T>::operator*( S & scalar)
    {
        Polynomial<T>& output = * new Polynomial<T>(Get_Size());
        for (int i = 0; i < Get_Size(); i++)
        {
            output[i] = Get(i)*scalar;
        }
        return output;
    }
    
    template <class T>
    void                Polynomial<T>::operator+=( Polynomial<T> & poly2)
    {
        int i = 0;
        Polynomial<T>& output = * new Polynomial<T>(max(Get_Size(), poly2.Get_Size()));
        T buffer;
        for (i; i < min(Get_Size(), poly2.Get_Size()); i++)
        {
            buffer = Get(i);
            buffer += poly2.Get(i);
            output.Set(buffer, i);

        }
        if (Get_Size() > poly2.Get_Size())
            for (i; i < max(Get_Size(), poly2.Get_Size()); i++)
                output.Set(Get(i), i);
        else
            for (i; i < max(Get_Size(), poly2.Get_Size()); i++)
                output.Set(poly2.Get(i), i);  
        *this = output;
    }
    
    template <class T>
    void                Polynomial<T>::operator*=( Polynomial<T> & poly2)
    {
        if (Get_Size() == 0 || poly2.Get_Size() == 0)
            return;
        Polynomial<T>& output = * new Polynomial<T>(Get_Size() + poly2.Get_Size() - 1);
        ArraySequence<bool> isFirst(output.Get_Size());
        for (int i = 0; i < output.Get_Size(); i++)
            isFirst[i] = true; 
        for (int i = 0; i < Get_Size(); i++)
        {
            for (int j = 0; j < poly2.Get_Size(); j++)
            {
                if (isFirst[i+j])
                {
                    output[i+j] = Get(i)*poly2.Get(j);
                    isFirst[i+j] = false;
                }     
                else
                    output[i+j] += Get(i)*poly2.Get(j);
            }
        }
        *this = output;
    }
    
    template <class T>
    template <class S>
    void                Polynomial<T>::operator*=( S & scalar)
    {
        Polynomial<T>& output = * new Polynomial<T>(Get_Size());
        for (int i = 0; i < Get_Size(); i++)
        {
            output[i] = Get(i)*scalar;
        }
        *this = output;
    } 
    template <class T>
    T&                Polynomial<T>::operator[](int index)
    {
        return (*polynom)[index];
    }