/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Theo Choma
 *
 * Created on April 24, 2017, 1:45 PM
 */

#include <cstdlib>
#include <valarray>
#include <iostream>

using namespace std;

/*
 * 
 */
class BaseConic{
    private:
        double x;
        double y;

    public:
        BaseConic(double x0 = 0, double y0 = 0);
        virtual ~BaseConic(){};
        void Move(double nx, double ny){x = nx; y = ny;}
        virtual double Area() const = 0; // a pure virtual function
        virtual void Display();
};







class Ellipse : BaseConic{
    private:
        double x;
        double y;
        double a; // semi-major axis
        double b; // semi-minor axis
        double angle; // orientation angle

    public:
        //void Move(double nx, double ny){x = nx; y = ny;}
        double Area() const
            {return 3.14159 * a * b;}
        void Rotate(double nang)
            {angle += nang;}
        void Resize(double na, double nb){a = na; b = nb;}
        void VertPos();
        void Display();
};

void Ellipse::VertPos(){
    double v1x, v1y, v2x, v2y, v3x, v3y, v4x, v4y;
    v1x = x + a;
    v1y = y;
    
    v2x = x - a;
    v2y = y;
    
    v3x = x;
    v3y = y + b;
    
    v4x = x;
    v4y = y - b;
    
    cout<<"Location of Vertices: "<<endl;
    cout<<"( "<<v1x<<", "<<v1y<<")"<<endl;
    cout<<"( "<<v2x<<", "<<v2y<<")"<<endl;
    
    cout<<"Location of Co-Vertices: "<<endl;
    cout<<"( "<<v3x<<", "<<v3y<<")"<<endl;
    cout<<"( "<<v4x<<", "<<v4y<<")"<<endl;
}

void Ellipse::Display(){
    cout<<"x = "<<x<<endl;
    cout<<"y = "<<y<<endl;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    cout<<"angle = "<<angle<<endl;
}







class Circle : BaseConic{
    private:
        double x;
        double y;
        double r; // radius

    public:
        //void Move(double nx, double ny){x = nx; y = ny;}
        double Area() const
        {return 3.14159 * r * r;}
        void Resize(double nr){r = nr;}
        void IsPt(double nx, double ny);
        void Display();
};

void Circle::Display(){
    cout<<"x = "<<x<<endl;
    cout<<"y = "<<y<<endl;
    cout<<"r = "<<r<<endl;
}

void Circle::IsPt(double nx, double ny){
    double d;
    d = sqrt((x-nx)*(x-nx) + (y-ny)*(y-ny));
    if (d == r)
        cout<<"Point is on the circle"<<endl;
    else if (d > r)
        cout<<"Point is outside the circle"<<endl;
    else if (d < r)
        cout<<"Point is inside the circle"<<endl;
    else
        cout<<"Error calculating d"<<endl;
}







int main() {

    return 0;
}

