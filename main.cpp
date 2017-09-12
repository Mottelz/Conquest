#include <iostream>
using namespace std;

int main() {
    int numOfLanguages;

    cout << "Hello reader.\n"
         << "Welcome to C++.\n";

    cout << "How many programming lanuages have you used? ";
    cin >> numOfLanguages;

    if (numOfLanguages < 1) {
        cout << "Read the preface!";
    }
    else {
        cout << "Enjoy the book.\n";
    }

    return 0;
}