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
        virtual ~BaseConic();
        void Move(double nx, double ny){x = nx; y = ny;}
        virtual double Area() const = 0; // a pure virtual function
        virtual void Display() = 0;
};

BaseConic::~BaseConic(){
}

BaseConic::BaseConic(double nx, double ny){
	x = nx;
	y = ny;
}







class Ellipse : public BaseConic{
    private:
        double x;
        double y;
        double a; // semi-major axis
        double b; // semi-minor axis
        double angle; // orientation angle

    public:
        void Move(double nx, double ny){x = nx; y = ny;}
        Ellipse(double,double,double,double,double);
        double Area() const
            {return 3.14159 * a * b;}
        void Rotate(double nang)
            {angle += nang;}
        void Resize(double na, double nb){a = na; b = nb;}
        void VertPos();
        void Display();
};

Ellipse::Ellipse(double na, double nb, double nx, double ny, double nang){
	a = na;
	b = nb;
	x = nx;
	y = ny;
	angle = nang;
}

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
        Circle(double,double,double);
        void Move(double nx, double ny){x = nx; y = ny;}
        double Area() const
        {return 3.14159 * r * r;}
        void Resize(double nr){r = nr;}
        void IsPt(double nx, double ny);
        void Display();
};

Circle::Circle(double nx, double ny, double nr){
	x = nx;
	y = ny;
	r = nr;
}

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

	Ellipse e1(1, 2, 3, 4, 5);
	cout<<"Area = "<<e1.Area()<<endl;
	e1.Resize(6,7);
	e1.Display();
	e1.Rotate(10);
	e1.Display();
	e1.VertPos();
	e1.Move(10,10);
	e1.Display();
	e1.VertPos();


	Circle c1(1, 2, 3);
	cout<<"Area = "<<c1.Area()<<endl;
	c1.Display();
	c1.IsPt(1, 2);
	c1.Move(5, 5);
	c1.Display();
	c1.Resize(7);
	c1.Display();

	BaseConic* p1 = &e1;
	p1->Display();


    return 0;
}
