/*	File:   billboard.h
	PROGRAMMER:  Dan Cliburn  (dcliburn@pacific.edu)
	PURPOSE:  The following is the description of a Billboard - a graphical entity that always
	faces the user.  For instance, rather than model a tree, we can show 
	a square picture of a tree that always faces the user, and make 
	portions of the image that don't belong to the tree invisible.  This
	gives 2D objects the illusion of being 3D.
   
   ACKNOWLEDGMENT: The idea for this class came from the text "OpenGL Game Programming", 
	by Kevin Hawkins and Dave Astle, pages 434-438.
*/
#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <math.h>
#include <fstream>
using namespace std;

class Vector
{
	private:
		double x;
		double y;
		double z;

	public:
		Vector (double x1 = 0, double y1 = 0, double z1 = 0)
		{x = x1; y = y1; z = z1;}

		double getX() {return x;}
		double getY() {return y;}
		double getZ() {return z;}

		void setX(double x1) {x = x1;}
		void setY(double y1) {y = y1;}
		void setZ(double z1) {z = z1;}

		Vector operator+(Vector v)
		{
			Vector result(v.x + x, v.y + y, v.z + z);
			return result;
		}

		Vector operator-(Vector v)
		{
			Vector result(x - v.x, y - v.y, z - v.z);
			return result;
		}

		friend Vector operator*(double scalar, Vector v)
		{
			Vector result(scalar * v.x, scalar * v.y, scalar * v.z);
			return result;
		}

		double length() {return sqrt(x*x + y*y + z*z);}

		Vector crossProduct(Vector v)
		{
			Vector result((y*v.y)-(v.y*z), -(x*v.z)-(v.x*z), (x*v.y)-(v.x*y));
			return result;
		}
};

class Point
{
	private:
		double x;
		double y;
		double z;

	public:
		Point (double x1 = 0, double y1 = 0, double z1 = 0)
		{x = x1; y = y1; z = z1;}

		double getX() {return x;}
		double getY() {return y;}
		double getZ() {return z;}

		void setX(double x1) {x = x1;}
		void setY(double y1) {y = y1;}
		void setZ(double z1) {z = z1;}

		Vector operator-(Point P)
		{
			Vector result(x - P.x, y - P.y, z - P.z);
			return result;
		}

		Point operator+(Point P)
		{
			Point result(x + P.x, y + P.y, z + P.z);
			return result;
		}

		friend Point operator*(double scalar, Point P)
		{
			Point result(scalar * P.x, scalar * P.y, scalar * P.z);
			return result;
		}

		Point operator+(Vector V)
		{
			Point result(V.getX() + x, V.getY() + y, V.getZ() + z);
			return result;
		}

		friend ostream &operator<<(ostream &out, Point &P)
		{
			out << P.x << " " << P.y << " " << P.z <<endl;
			return out;
		}

		void getCoords(double *pts)
		{
			*pts = x;
			*(pts+1) = y;
			*(pts+2) = z;
		}
};

class Billboard
{
	protected:  //protected so that the Billboard class can serve as a BASE CLASS
		int id; //texture ID
		Point P;  //center point of the billboard

	public:
		//Class Constructors
		Billboard(double x = 0, double y = 0, double z = 0);
		Billboard(char fileName[], int ID, double x = 0, double y = 0, double z = 0);

		void setPosition(double x = 0, double y = 0, double z = 0);

		void setX(double x) {P.setX(x);}
		void setY(double y) {P.setY(y);}
		void setZ(double z) {P.setZ(z);}

		double getX() {return P.getX();}
		double getY() {return P.getY();}
		double getZ() {return P.getZ();}

		//If billboard is used in a particle system, we only need to load texture once.
		//Having the set method allows us to just set the ID manually, rather than call load
		void setID(int ID) {id = ID;}

		void load(char fileName[], int ID);

		void draw(double size = 1.0, bool BLENDING = false);
};

#endif