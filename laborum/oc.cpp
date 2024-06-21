#include <iostream>
#include <cmath>

int main() {
    float2 myVector = float2(3.5f, 2.0f);
    
    std::cout << "Vector x-component: " << myVector.x << std::endl;
    std::cout << "Vector y-component: " << myVector.y << std::endl;
    
    // Perform some calculations with the vector
    float magnitude = std::sqrt(myVector.x * myVector.x + myVector.y * myVector.y);
    std::cout << "Vector magnitude: " << magnitude << std::endl;
    
    return 0;
}
