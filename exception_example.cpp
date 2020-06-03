// runtime_error.cpp
// compile with: /EHsc /GR
#include <iostream>
#include <typeinfo>
#include <string>
#include "table.h"
#include <stdio.h> 
#include <time.h>
#include "hashTable.h"
#include "avltree.h"

using namespace std;

class PositiveNumber
{
    int positiveNumber;
public:
    PositiveNumber(int num) :positiveNumber(num)
    {
        if (num < 0)
            throw exception("negative number");
    }
};

int main()
{
    /*
    //string a = "1";
    int a = -1;
    auto& ti1 = typeid(a);
    cout << ti1.name() << endl;
    // runtime_error
    try
    {
        PositiveNumber n(a);
    }
    catch (exception &e)
    {
        cerr << "Caught " << e.what() << endl;
        cerr << "Type " << typeid(e).name() << endl;
    };*/

    /*
    Table<int, int> test1(3);
    test1.Add(0, 3);
    test1.Add(1, 1);
    test1.Add(2, 2);
    for (int i = 0; i < 3; i++)
        cout << test1.Find(i) << " ";

    SortTable<int, int> sortTest1(test1);
    sortTest1.Delete(1);
    try { sortTest1.Find(1); }
    catch (...)
    { 
        cerr << "\nCaught exeption\n";
    }
    cout << sortTest1.Find(0) << endl;*/
    /*
    HashTable<int, int> hashtest(10);

    hashtest.Add(1, 18);
    hashtest.Add(11, 22);

    //hashtest.Delete(1);
   
    cout << hashtest.Find(1);
    
    Data &data = hashtest.Find(1);
    if(data != hashtest.End())
        data++;
    cout << endl << hashtest.Find(1);
    */
    
    
    AVLTree<string> test(2, "Test2");
    test.insert(1,"Test1");
    test.insert(3, "Test3");
    test.insert(4, "Test4");
    cout << test.find(3) << endl;
    test.remove(3);
    test.remove(1);



    system("pause");
}


/* Output:
Caught bad locale name
Type class std::runtime_error
*/

