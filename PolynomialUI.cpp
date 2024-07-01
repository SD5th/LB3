#include "C:\Main\Kodiki\C++\SimpleConsoleUI\SimpleConsoleUI.h"
#include "C:\Main\Kodiki\C++\SimpleConsoleUI\SimpleConsoleUI.h"
#include "Polynomial.h"
#include "SquareMatrix.h"
#include "ComplexNumber.h"
#include <stdio.h>

using namespace std;

Shell* Head;
Shell* ChooseType;
Shell* CreatePolynomial;
Shell* ListOfPolynomials;
Shell* PolynomialOperations;
Shell* SetOperation;
Shell* ResizeOperation;
Shell* ComposeOperation;
Shell* EvaluateOperation;
Shell* Exit;



struct AllPolynomials
{
    enum PolType
    {
        IntType,
        FloatType,
        ComplexType,
        MatrixType,
        NoneType
    };
    PolType type;
    ArraySequence<Polynomial<int>*>    IntPols;
    ArraySequence<string>               IntPolNames;
    ArraySequence<Polynomial<float>*>  FloatPols;
    ArraySequence<string>               FloatPolNames;
    ArraySequence<Polynomial<ComplexNumber>*> ComplexPols;
    ArraySequence<string>                      ComplexPolNames;
    ArraySequence<Polynomial<SquareMatrix<int>>*> MatrixPols;
    ArraySequence<string>                          MatrixPolNames;

    AllPolynomials():
        type(NoneType),
        IntPols(),
        IntPolNames(),
        FloatPols(),
        FloatPolNames(),
        ComplexPols(),
        ComplexPolNames(),
        MatrixPols(),
        MatrixPolNames()
    { }
};

AllPolynomials AP = AllPolynomials();


void Head_Function()
{
    cout << "Hello! This is User Interface for Polynomial.h\n";
    Head->Set_Function(nullptr);
}

void ChooseType_Function()
{
    cout << "Choose type of data to work with:\n"
         << "Input 'Int', 'Float', 'Complex'.\n"; // or 'Matrix'
    string polType;
    getline(cin, polType);
    while(polType != "Int" && polType != "Float" && polType != "Complex" && polType != "Matrix")
    {
        cout << "Wrong! Input 'Int', 'Float', 'Complex' or 'Matrix'.\n";
        getline(cin, polType);
    }
    if (polType == "Int")
    {
        cout << "Got it. Let's work with integers.\n";
        AP.type = AllPolynomials::PolType::IntType;
    }
    else if (polType == "Float")
    {
        cout << "Got it. Let's work with float numbers.\n";
        AP.type = AllPolynomials::PolType::FloatType;
    }
    else if (polType == "Complex")
    {
        cout << "Got it. Let's work with complex numbers.\n";
        AP.type = AllPolynomials::PolType::ComplexType;
    }
    // else if (polType == "Matrix")
    // {
    //     cout << "Got it. Let's work with square matrixes of integers.\n";
    //     AP.type = AllPolynomials::PolType::MatrixType;
    // }    

}

void CreatePolynomial_Function()
{
    cout << "Let's create polynomial.\n"
         << "Input name of new polynomial.\n";
    string name;
    getline(cin, name);
    while (name.size() == 0){
        cout << "Empty name, try another\n.";
        getline(cin, name);
    }
    cout << "Now input degree of polynomial.\n";
    int degree;
    cin >> degree;
    switch (AP.type)
    {
    case AllPolynomials::IntType:
        AP.IntPols.Append(new Polynomial<int>(degree+1));
        AP.IntPolNames.Append(name);
        break;
    case AllPolynomials::FloatType:
        AP.FloatPols.Append(new Polynomial<float>(degree+1));
        AP.FloatPolNames.Append(name);
        break;
    case AllPolynomials::ComplexType:
        AP.ComplexPols.Append(new Polynomial<ComplexNumber>(degree+1));
        AP.ComplexPolNames.Append(name);
        break;
    case AllPolynomials::MatrixType:{

        int matrixSize;
        cout << "Input size of each matrix.\n";
        cin >> matrixSize;
        ArraySequence<SquareMatrix<int>>* bufArr;
        for (int i = 0; i < degree + 1; i++)
        {
            bufArr->Append( *(new SquareMatrix<int>(matrixSize)));
        }
        Polynomial<SquareMatrix<int>>* bufPoly = new Polynomial<SquareMatrix<int>>(bufArr);
        AP.MatrixPols.Append(bufPoly);

        AP.MatrixPolNames.Append(name);
        break;
    }
    
    default:
        cout << "unknown poly type";
    }
}

string intToX(int num)
{

    string out = "";
    if (num == 0)
        return "1";
    while (num != 0)
    {
        switch (num % 10)
        {
        case 0:
            out = "⁰" + out;
            break;
        case 1:
            out = "¹" + out;
            break;
        case 2:
            out = "²" + out;
            break;
        case 3:
            out = "³" + out;
            break;
        case 4:
            out = "⁴" + out;
            break;
        case 5:
            out = "⁵" + out;
            break;
        case 6:
            out = "⁶" + out;
            break;
        case 7:
            out = "⁷" + out;
            break;
        case 8:
            out = "⁸" + out;
            break;
        case 9:
            out = "⁹" + out;
            break;
        default:
            break;
        }
        num /= 10;
    }
    out = "x" + out;
    return out;
}

void ListOfPolynomials_Function()
{
    cout << "List of all Polynomials:\n";
    switch (AP.type)
    {
    case AllPolynomials::IntType:
        for (int i = 0; i < AP.IntPols.GetSize(); i++)
        {
            cout << i+1 << ") Name: " << AP.IntPolNames[i] << "\n"
                 << "Degree: " << AP.IntPols.Get(i)->Get_Size() - 1 << "\n"
                 << "Items: \n";
            if (AP.IntPols.Get(i)->Get_Size() != 0)
            {
                int j = AP.IntPols.Get(i)->Get_Size() - 1;
                cout << AP.IntPols.Get(i)->Get(j) << '*' << intToX(j);
                for (j = j - 1; j >= 0; j -= 1)
                    cout <<" + " << AP.IntPols.Get(i)->Get(j) << '*' << intToX(j);
                cout << "\n\n";
            }
        }
        break;
    case AllPolynomials::FloatType:
        for (int i = 0; i < AP.FloatPols.GetSize(); i++)
        {
            cout << i+1 << ") Name: " << AP.FloatPolNames[i] << "\n"
                 << "Degree: " << AP.FloatPols.Get(i)->Get_Size() - 1 << "\n"
                 << "Items: \n";
            if (AP.FloatPols.Get(i)->Get_Size() != 0)
            {
                int j = AP.FloatPols.Get(i)->Get_Size() - 1;
                cout << AP.FloatPols.Get(i)->Get(j) << '*' << intToX(j);
                for (j = j - 1; j >= 0; j -= 1)
                    cout <<" + " << AP.FloatPols.Get(i)->Get(j) << '*' << intToX(j);
                cout << "\n\n";
            }        
        }        
        break;
    case AllPolynomials::ComplexType:
        for (int i = 0; i < AP.ComplexPols.GetSize(); i++)
        {
            cout << i+1 << ") Name: " << AP.ComplexPolNames[i] << "\n"
                 << "Degree: " << AP.ComplexPols.Get(i)->Get_Size() - 1 << "\n"
                 << "Items: \n";
            if (AP.ComplexPols.Get(i)->Get_Size() != 0)
            {
                int j = AP.ComplexPols.Get(i)->Get_Size() - 1;
                cout << "(" << AP.ComplexPols.Get(i)->Get(j).real << "+" << AP.ComplexPols.Get(i)->Get(j).imag << "*i)*" << intToX(j);
                for (j = j - 1; j >= 0; j -= 1)
                    cout << " + (" << AP.ComplexPols.Get(i)->Get(j).real << "+" << AP.ComplexPols.Get(i)->Get(j).imag << "*i)*" << intToX(j);

                cout << "\n\n";
            }        
        }
        break;
    case AllPolynomials::MatrixType:
        for (int i = 0; i < AP.MatrixPols.GetSize(); i++)
        {
            cout << i+1 << ") Name: " << AP.MatrixPolNames[i] << "\n"
                 << "Degree: " << AP.MatrixPols.Get(i)->Get_Size() - 1 << "\n"
                 << "Items: \n";
            
            int j = AP.MatrixPols.Get(i)->Get_Size() - 1;
            for (int row = 0; row < AP.MatrixPols.Get(i)->Get(j).Get_Size(); row++)
                {
                    cout << "\n|";
                    for (int column = 0; column < AP.MatrixPols.Get(i)->Get(j).Get_Size(); column++)
                        printf("%3d ", AP.MatrixPols.Get(i)->Get(j)[row][column]);
                    cout << "|";
                }
            cout << " * " << intToX(j) << "\n";
            for (int j = j - 1; j >= 0; j -= 1)
            {
                for (int row = 0; row < AP.MatrixPols.Get(i)->Get(j).Get_Size(); row++)
                {
                    cout << "\n|";
                    for (int column = 0; column < AP.MatrixPols.Get(i)->Get(j).Get_Size(); column++)
                        printf("%3d ", AP.MatrixPols.Get(i)->Get(j)[row][column]);
                    cout << "|";
                }
                cout << " * " << intToX(j) << "\n";
            }


        }
        break;
    
    default:
        cout << "unknown poly type";
    }
}

void SetOperation_Function()
{
    cout << "Choose Polynomial to Set.\n";
    int number, index;
    switch (AP.type)
    {
    case AllPolynomials::IntType:
        int intItem;
        cout << "From 1 to " << AP.IntPols.GetSize() << "\n";
        cin >> number;
        cout << "Input index to Set.\n";
        cout << "From 0 to " << AP.IntPols.Get(number-1)->Get_Size()-1 << ".\n";
        cin >> index;
        cout << "Input item to Set.\n";
        cin >> intItem;
        AP.IntPols.Get(number-1)->Set(intItem, index);
        break;

    case AllPolynomials::FloatType:
        float floatItem;
        cout << "From 1 to " << AP.FloatPols.GetSize() << "\n";
        cin >> number;
        cout << "Input index to Set.\n";
        cout << "From 0 to " << AP.FloatPols.Get(number-1)->Get_Size()-1 << ".\n";
        cin >> index;
        cout << "Input item to Set.\n";
        cin >> floatItem;
        AP.FloatPols.Get(number-1)->Set(floatItem, index);
        break;

    case AllPolynomials::ComplexType:
        float complexBuffer1;
        float complexBuffer2;
        cout << "From 1 to " << AP.ComplexPols.GetSize() << "\n";
        cin >> number;
        cout << "Input index to Set.\n";
        cout << "From 0 to " << AP.ComplexPols.Get(number-1)->Get_Size()-1 << ".\n";
        cin >> index;
        cout << "Input real part of item to Set.\n";
        cin >> complexBuffer1;
        cout << "Input imaginary part of item to Set.\n";
        cin >> complexBuffer2;

        AP.ComplexPols.Get(number-1)->Set(ComplexNumber(complexBuffer1, complexBuffer2), index);
        break;

    case AllPolynomials::MatrixType:
    {
        int intBuffer;
        cout << "From 1 to " << AP.MatrixPols.GetSize() << "\n";
        cin >> number;
        cout << "Input index to Set.\n";
        cout << "From 0 to " << AP.MatrixPols.Get(number-1)->Get_Size()-1 << ".\n";
        cin >> index;
        cout << "Input matrix to Set.\n";
        for (int row = 0; row < AP.MatrixPols.Get(index)->Get_Size(); row++)
            for (int column = 0; column < AP.MatrixPols.Get(index)->Get_Size(); column++)
                {
                    cin >> intBuffer;
                    AP.MatrixPols.Get(index)[row][column] = intBuffer;
                } 
        break;
    }

    default:
        cout << "unknown poly type";
    }

    cout << "Ready!\n";
}

void ResizeOperation_Function()
{
    int number, newSize;
    cout << "Choose Polynomial to Resize.\n";
    switch (AP.type)
    {
    case AllPolynomials::IntType:
        cout << "From 1 to " << AP.IntPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        cout << "Input new size.\n";
        cin >> newSize;
        AP.IntPols.Get(number-1)->Resize(newSize);
        break;

    case AllPolynomials::FloatType:
        cout << "From 1 to " << AP.FloatPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        cout << "Input new size.\n";
        cin >> newSize;
        AP.FloatPols.Get(number-1)->Resize(newSize);
        break;

    case AllPolynomials::ComplexType:
        cout << "From 1 to " << AP.ComplexPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        cout << "Input new size.\n";
        cin >> newSize;
        AP.ComplexPols.Get(number-1)->Resize(newSize);
        break;

    case AllPolynomials::MatrixType:
        cout << "From 1 to " << AP.MatrixPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        cout << "Input new size.\n";
        cin >> newSize;
        AP.MatrixPols.Get(number-1)->Resize(newSize);
        break;
    

    default:
        cout << "unknown poly type";
    }
    cout << "Ready!\n";
}

void ComposeOperation_Function()
{
    cout << "Choose Polynomial to Compose as f(x).\n";
    int numberFx, numberGx;
    switch (AP.type)
    {
    case AllPolynomials::IntType:
    {
        cout << "From 1 to " << AP.IntPols.GetSize() << "\n";
        cin >> numberFx;
        cout << "Choose Polynomial to Compose as g(x).\n"
             << "From 1 to " << AP.IntPols.GetSize() << "\n";
        cin >> numberGx;
        numberFx -= 1;
        numberGx -= 1;
        Polynomial<int> composition = AP.IntPols.Get(numberFx)->Compose(*(AP.IntPols.Get(numberGx)));
        Polynomial<int> * buffer = new Polynomial<int>(composition);
        AP.IntPols.Append(buffer);
        AP.IntPolNames.Append("Composition: " + AP.IntPolNames.Get(numberFx) + " o " + AP.IntPolNames.Get(numberGx));
        break;
    }
    case AllPolynomials::FloatType:
    {
        cout << "From 1 to " << AP.FloatPols.GetSize() << "\n";
        cin >> numberFx;
        cout << "Choose Polynomial to Compose as g(x).\n"
             << "From 1 to " << AP.FloatPols.GetSize() << "\n";
        cin >> numberGx;
        numberFx -= 1;
        numberGx -= 1;
        Polynomial<float> composition = AP.FloatPols.Get(numberFx)->Compose(*(AP.FloatPols.Get(numberGx)));
        Polynomial<float> * buffer = new Polynomial<float>(composition);
        AP.FloatPols.Append(buffer);        
        AP.FloatPolNames.Append("Composition: " + AP.FloatPolNames.Get(numberFx) + " o " + AP.FloatPolNames.Get(numberGx));
        break;
    }
        
    case AllPolynomials::ComplexType:
    {
        cout << "From 1 to " << AP.ComplexPols.GetSize() << "\n";
        cin >> numberFx;
        cout << "Choose Polynomial to Compose as g(x).\n"
             << "From 1 to " << AP.ComplexPols.GetSize() << "\n";
        cin >> numberGx;
        numberFx -= 1;
        numberGx -= 1;
        Polynomial<ComplexNumber> composition = AP.ComplexPols.Get(numberFx)->Compose(*(AP.ComplexPols.Get(numberGx)));
        Polynomial<ComplexNumber> * buffer = new Polynomial<ComplexNumber>(composition);
        AP.ComplexPols.Append(buffer);        
        AP.ComplexPolNames.Append("Composition: " + AP.ComplexPolNames.Get(numberFx) + " o " + AP.ComplexPolNames.Get(numberGx));
        break;
    }
    case AllPolynomials::MatrixType:
    {
        cout << "From 1 to " << AP.MatrixPols.GetSize() << "\n";
        cin >> numberFx;
        cout << "Choose Polynomial to Compose as g(x).\n"
             << "From 1 to " << AP.MatrixPols.GetSize() << "\n";
        cin >> numberGx;
        numberFx -= 1;
        numberGx -= 1;
        Polynomial<SquareMatrix<int>> composition = AP.MatrixPols.Get(numberFx)->Compose(*(AP.MatrixPols.Get(numberGx)));
        Polynomial<SquareMatrix<int>> * buffer = new Polynomial<SquareMatrix<int>>(composition);
        AP.MatrixPols.Append(buffer);        
        AP.MatrixPolNames.Append("Composition: " + AP.MatrixPolNames.Get(numberFx) + " o " + AP.MatrixPolNames.Get(numberGx));
        break;
    }
    default:
    {
        cout << "unknown poly type";
    }
    }
    cout << "Ready!\n";

}

void EvaluateOperation_Function()
{
    int number;
    cout << "Choose Polynomial to Evaluate.\n";
    switch (AP.type)
    {

    case AllPolynomials::IntType:
    {

        cout << "From 1 to " << AP.IntPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        int intPoint;

        cout << "Input point.\n";

        cin >> intPoint;

        cout << "Result of evaluation:\n"
             << AP.IntPols.Get(number)->EvaluateAtPoint(intPoint);
         break;
    }

    case AllPolynomials::FloatType:
    {
        cout << "From 1 to " << AP.FloatPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        float floatPoint;

        cout << "Input Point.\n";

        cin >> floatPoint;
        cout << "Result of evaluation:\n"
             << AP.FloatPols.Get(number)->EvaluateAtPoint(floatPoint);
        break;
    }

    case AllPolynomials::ComplexType:
    {
        cout << "From 1 to " << AP.ComplexPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        float complexBuffer1;

        float complexBuffer2;

        cout << "Input real part of Point.\n";

        cin >> complexBuffer1;

        cout << "Input imaginary part of Point.\n";

        cin >> complexBuffer2;

        cout << "Result of evaluation:\n"
             << AP.ComplexPols.Get(number)->EvaluateAtPoint(ComplexNumber(complexBuffer1, complexBuffer2)).real
             << " +" << AP.ComplexPols.Get(number)->EvaluateAtPoint(ComplexNumber(complexBuffer1, complexBuffer2)).imag << "*i\n";
        break;
    }

    case AllPolynomials::MatrixType:
    {
        cout << "From 1 to " << AP.MatrixPols.GetSize() << "\n";
        cin >> number;
        number -= 1;
        int intBuffer;
        cout << "Input point matrix " << AP.MatrixPols.Get(number)->Get(0).Get_Size() << "x" << AP.MatrixPols.Get(number)->Get(0).Get_Size() << ".\n";
        SquareMatrix<int> matrixItem(AP.MatrixPols.Get(0)->Get_Size());
        for (int row = 0; row < matrixItem.Get_Size(); row++)
            for (int column = 0; column < matrixItem.Get_Size(); column++)
                {
                    cin >> intBuffer;
                    matrixItem[row][column] = intBuffer;
                } 
        SquareMatrix<int> answer = AP.MatrixPols.Get(number)->EvaluateAtPoint(matrixItem);
        for (int row = 0; row < answer.Get_Size(); row++)
                {
                    cout << "\n|";
                    for (int column = 0; column < answer.Get_Size(); column++)
                        printf("%3d ", answer[row][column]);
                    cout << "|";
                }

        break;
    }
    

    default:
        cout << "unknown poly type";
    }
        cout << "\nPress Enter to Continue.\n";
        string enter;
        getline(cin, enter);
        
}

void Exit_Function()
{
    cout << "Confirm exit from the program. Type EXIT\n";
    string UserText; 
    getline(cin, UserText);
    if (UserText == "EXIT")
    {
        cout << "So sad.. Bye!\n"; 
        exit(1);
    }
    else 
    {
        cout << "Then let's stay together!\n";
    }
}

int main()
{
    Head =                 new Shell("Head Window",         Head_Function, new Connector);
    ChooseType =           new Shell("Choose Type",         ChooseType_Function, new Connector);
    CreatePolynomial =     new Shell("Create Polynomial",     CreatePolynomial_Function, new Connector);
    ListOfPolynomials =    new Shell("List of Polynomials",   ListOfPolynomials_Function, new Connector);
    PolynomialOperations = new Shell("Polynomial Operations", nullptr, new Connector);
    SetOperation =         new Shell("Set",                 SetOperation_Function, new Connector);
    ResizeOperation =      new Shell("Resize",              ResizeOperation_Function, new Connector);
    ComposeOperation =     new Shell("Compose",              ComposeOperation_Function, new Connector);
    EvaluateOperation =    new Shell("Evaluate",              EvaluateOperation_Function, new Connector);
    Exit =                 new Shell("Exit",                Exit_Function, new Connector);

    Head->Get_Connector()->Append_Shell(ChooseType);
    Head->Get_Connector()->Append_Shell(ListOfPolynomials);
    Head->Get_Connector()->Append_Shell(CreatePolynomial);
    Head->Get_Connector()->Append_Shell(PolynomialOperations);

    ChooseType->Get_Connector()->Append_Shell(Head);

    Head->Get_Connector()->Append_Shell(Exit);
    
    CreatePolynomial->Get_Connector()->Append_Shell(Head);

    ListOfPolynomials->Get_Connector()->Append_Shell(Head);

    PolynomialOperations->Get_Connector()->Append_Shell(SetOperation);
    PolynomialOperations->Get_Connector()->Append_Shell(ResizeOperation);
    PolynomialOperations->Get_Connector()->Append_Shell(ComposeOperation);
    PolynomialOperations->Get_Connector()->Append_Shell(EvaluateOperation);
    PolynomialOperations->Get_Connector()->Append_Shell(Head);

    SetOperation->Get_Connector()->Append_Shell(SetOperation);
    SetOperation->Get_Connector()->Append_Shell(Head);

    ResizeOperation->Get_Connector()->Append_Shell(Head);

    ComposeOperation->Get_Connector()->Append_Shell(Head);

    EvaluateOperation->Get_Connector()->Append_Shell(EvaluateOperation);
    EvaluateOperation->Get_Connector()->Append_Shell(Head);
        
    Exit->Get_Connector()->Append_Shell(Head);

    ActiveShell Active(ChooseType, ActiveShell::VScode);
    Active.StartUI();
}