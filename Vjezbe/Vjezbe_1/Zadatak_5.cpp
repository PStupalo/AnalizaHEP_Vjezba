#include <iostream>

// Funkcija koja računa kub broja
double _my_cube(double x) {
    return x * x * x;
}

int main() {
    double number;
    std::cout << "Unesite realan broj: ";
    std::cin >> number; //ucitava uneseni br

    double result = _my_cube(number);
    std::cout << "Kub broja " << number << " je " << result << std::endl;

    return 0;
}
