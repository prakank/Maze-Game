#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>

class Vector2D
{
    public:
        float x,y;

        Vector2D();
        Vector2D(float x, float y);

        Vector2D& Add(const Vector2D& v); // v1.add(v2);    
        Vector2D& Subtract(const Vector2D& v);
        Vector2D& Multiply(const Vector2D& v);
        Vector2D& Divide(const Vector2D& v);
    
        // Operator overloading

        // FRIEND
        // friend operator function takes two parameters in a binary operator, 
        // varies one parameter in a unary operator. All the working and implementation 
        // would same as binary operator function except this function will be implemented outside of the class scope.
        
        friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
        // Friend function will take two arguments for binary operator overloading

        Vector2D& operator+=(const Vector2D& v);
        Vector2D& operator-=(const Vector2D& v);
        Vector2D& operator*=(const Vector2D& v);
        Vector2D& operator/=(const Vector2D& v);

        Vector2D& operator*(const int& i);
        Vector2D& Zero();

        // Overloading output stream
        friend std::ostream& operator<<(std::ostream stream, const Vector2D& v); 
};

#endif