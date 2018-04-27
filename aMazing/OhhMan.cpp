//Gerard Cancino

/*
Z=Z^2 + C
C=1;
Z=0 //1st Iteration
1) Z = 0 + 1
Z=1
2) Z = 1^2 + 1;
Z=2;
3) Z = 2^2 + 1;
Z=5;
4) Z = 5^2 + 1;
Z=26;
*/
// No^

//??? Produced image, but wasnt the picture on colorado

#include <iostream>
#include <math.h>
#include "graphics.h"
using namespace std;

//PreCondition: input the current index
//PostCondition: return the Cartesian value from -2 to 2
double coordChangeCart(const int i);
//PreCondition: input the coords
//PostCondition: return the hypotenuse from the origin
double distanceFromOrigin(double x, double y);
//PreCondition: input the current coord
//PostCondition: return a number between 1-15 representing the number of jumps
int escapeColor(const double x,const double y);

int main() {
	int pixelSize = 401;
	int finalwindow = initwindow(pixelSize, pixelSize,"first");
	int exitwindow = initwindow(200, 50, "Exit");
	setcurrentwindow(finalwindow);
	/*
	cout << distanceFromOrigin(200, 200) << endl;
	cout << distanceFromOrigin(0, 0) << endl;
	cout << distanceFromOrigin(400, 400) << endl;
	*/
	//Test
	/*
	double movingX = 0.5;
	double movingY = 1.0;
	double xCoordCart = movingX;
	double yCoordCart = movingY;
	double movingX2 = movingX;
	movingX = (movingX * movingX) - (movingY * movingY) + xCoordCart;
	movingY = (2 * movingX2 * movingY) + yCoordCart;
	cout << movingX << " " << movingY << endl;
	movingX = (movingX * movingX) - (movingY * movingY) + xCoordCart;
	movingY = (2 * movingX2 * movingY) + yCoordCart;
	cout << movingX << " " << movingY << endl;

	movingX = 0.1;
	movingY = -1.9;
	cout << movingX << " " << movingY << endl;
	movingX = (movingX * movingX) - (movingY * movingY) + xCoordCart;
	movingY = (2 * movingX2 * movingY) + yCoordCart;
	cout << movingX << " " << movingY << endl;

	*/

	for (int i = 0; i < 401; i++) {
		for(int j = 0; j < 401; j++){
			int color = escapeColor(coordChangeCart(i), coordChangeCart(j));
			putpixel(i,j,color);
		}
	}
	/*
	while (!ismouseclick(WM_LBUTTONDOWN))

	{
		delay(500);

	}


	int x = 0;
	int y = 0;
	getmouseclick(WM_LBUTTONDOWN, x, y);

	cout << "The mouse was clicked at: ";

	cout << "x=" << x;

	cout << " y=" << y << endl;
	*/

	setcurrentwindow(exitwindow);
	outtextxy(0, 0, "Press any key");
	getch();
	return 1;
}


/*
x=0
trux=-2
x=400
truex=2
x=200
truex=0
Y=mx+b
Y-y1=m(x-x1)+b
Y-200=m(x-200)+b


Y      X
0     -2
50    -1.5?
100   -1?
200    0
300    1?
400    2

m = 100;

Y=100x+200
Y=100(1)=200
300


(Y-200)/100 = x
(300-200)/100=x
100/100=1

(50-200)/100=x
-150/100=x
-1.5=x

*/


double coordChangeCart(const int index) {
	double cart;
	cart = (double)(index - 200) / 100;
	return cart;
}

//a^2+b^2=c^2
double distanceFromOrigin(const double a,const double b) {
	//a*a + b*b = c*c
	double c, c2;
	c2 = a*a + b*b;
	c = sqrt(c2);
	return c;
}

/*
x=1 y =1
t=1-1+1
l=2*1*1+1
l=4

t=0.25-1+0.5=-0.25

x=0
y=-2
t=0-4+0 = -4;
l=2*0*-2-2 = -2;

x=0;

*/


int escapeColor(const double xCoordCart,const double yCoordCart) {
	int jumpNum = 0;
	double movingX = xCoordCart;
	double movingY = yCoordCart;
	double distance = distanceFromOrigin(movingX, movingY);
	while (movingX <= 2 && movingY <= 2 && movingX >= -2 && movingY >= -2 && jumpNum < 15 && distance <= 2){
		double movingX2 = movingX;
		movingX = (movingX * movingX) - (movingY * movingY) + xCoordCart;
		movingY = (2*movingX2 * movingY) + yCoordCart;
		//if (movingX <= 2 && movingY <= 2 && movingX >= -2 && movingY >= -2 || distance <= 2)
			jumpNum++;
		distance = distanceFromOrigin(movingX, movingY);
	}
	return jumpNum;
}
