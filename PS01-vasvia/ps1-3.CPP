#include <iostream>
#include <iomanip>
#include <cmath>

int main() {

    // initializing the values
    double a,b,c,d,e,f;

    // inputs for the values
    std::cout <<"ax+by=c \n" << std::endl;
    std::cout <<"dx+ey=f \n" << std::endl;
    std::cout <<"Enter the values of a b c d e f: ";
    std::cin >> a >> b >> c >> d >> e >> f;

    // finding the determinant of the equation
    double det = a * e - b * d;

    if (std::abs(det) < 0.000001)
    {
        std::cout << "No Solution \n"; // raising errors
    } 
    else
    {
        // solving for values 
        double x = (e * c - b * f) / det;
        double y = (a * f - c * d)/det;

        // printing the values
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "x=" << x << "y=" << y <<std::endl;
    }

    return 0;

}