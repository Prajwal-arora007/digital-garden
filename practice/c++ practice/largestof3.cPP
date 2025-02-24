#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a,b,c;
    cout << "Enter three numbers";
    cin>>a>>b>>c;
    if(a>b)
    {
        if(b>c)
            cout<<"a>b>c";
        else if (c>b)
            cout<<"a>c>b";
        else 
            cout<<"a>b=c";
    }
    else if(b>a)
    {
        if(a>c)
            cout<<"b>a>c";
        else if(c>a)
            cout<<"b>c>a";
        else
            cout<<"b>c=a";
    }
    else if(c>a)
    {
        if(a>b)
            cout<<"c>a>b";
        else if(b>a)
            cout<<"c>b>a";
        else
            cout<<"c>b=a";
    }
    else
    {
        cout<<"a=b=c";
    }

    return 0;
}
