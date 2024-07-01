class ComplexNumber
{
    public:
        float real;
        float imag;

        // конструкторы-деструкторы
        ComplexNumber(float, float);
        ComplexNumber();

        // операции

        // перегрузка операторов
            ComplexNumber operator+(ComplexNumber);
            ComplexNumber operator-(ComplexNumber);
            ComplexNumber operator*(ComplexNumber);
            ComplexNumber operator/(ComplexNumber);
            void operator+=(ComplexNumber);
            void operator-=(ComplexNumber);
            void operator*=(ComplexNumber);
            void operator/=(ComplexNumber);
            
};

ComplexNumber::ComplexNumber()
{ }  
ComplexNumber::ComplexNumber(float real, float imag):
    real(real),
    imag(imag)
{ }


ComplexNumber ComplexNumber::operator+(ComplexNumber complex)
{
    return ComplexNumber(real + complex.real, imag + complex.imag);
}
ComplexNumber ComplexNumber::operator-(ComplexNumber complex)
{
    return ComplexNumber(real - complex.real, imag - complex.imag);
}
ComplexNumber ComplexNumber::operator*(ComplexNumber complex)
{
    return ComplexNumber
    (
        real*complex.real - imag*complex.imag, 
        imag*complex.real - real*complex.imag
    );
}
ComplexNumber ComplexNumber::operator/(ComplexNumber complex)
{
    return ComplexNumber
    (
        (real*complex.real + imag*complex.imag) / (complex.real*complex.real + complex.imag*complex.imag),
        (complex.real*imag - real*complex.imag) / (complex.real*complex.real + complex.imag*complex.imag)
    );
}
void ComplexNumber::operator+=(ComplexNumber complex)
{
    real += complex.real;
    imag += complex.imag;
}
void ComplexNumber::operator-=(ComplexNumber complex)
{
    real -= complex.real;
    imag -= complex.imag;
}
void ComplexNumber::operator*=(ComplexNumber complex)
{
    ComplexNumber buffer
    (
        real*complex.real - imag*complex.imag, 
        imag*complex.real - real*complex.imag
    );
    *this = buffer;
}
void ComplexNumber::operator/=(ComplexNumber complex)
{
    ComplexNumber buffer
    (
        (real*complex.real + imag*complex.imag) / (complex.real*complex.real + complex.imag*complex.imag),
        (complex.real*imag - real*complex.imag) / (complex.real*complex.real + complex.imag*complex.imag)
    );
    *this = buffer;
}


template <typename T>
ComplexNumber complex(T number)
{
    return ComplexNumber(number, 0);
}
