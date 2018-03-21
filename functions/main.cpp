#include <iostream>
#include <list>
#include <string>

using namespace std;

void func1(void)
{
    cout << "--------------------" << endl;
    cout << "func1 called" << endl;
    cout << "--------------------" << endl << endl;
}

void func2(int *arg)
{
    cout << "--------------------" << endl;
    cout << "func2 called with arg=" << *arg << endl;
    cout << "--------------------" << endl << endl;
}

void func3(list<string> ls)
{
    cout << "--------------------" << endl;
    cout << "func3 called" << endl;
    cout << "--------------------" << endl;
    for(auto it = ls.begin(); it != ls.end(); it++){
        cout << *(it) << endl;
    }
    cout << "--------------------" << endl;
}

void callVoid(void (*func)(void))
{
    func();
}

void callInt(void (*func)(int*))
{
    int x = 500;
    func(&x);
}

void callList(void (*func)(list<string>))
{
    list<string> ls = {"Hello","My","World"};
    func(ls);
}

int main()
{
    callVoid(func1);
    callInt(func2);
    callList(func3);
    return 0;
}
