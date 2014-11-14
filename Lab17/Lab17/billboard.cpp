/*	FILE:		billboard.cpp
	PROGRAMMER:	Dan Cliburn
	PURPOSE:	Defines the methods for the Billboard class.
*/

#include "billboard.h"
#include "texture.h"
#include "Windows.h"
#include <gl\GL.h>

Billboard::Billboard(double x, double y, double z)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
	P.setX(x);
	P.setY(y);
	P.setZ(z);
}

Billboard::Billboard(char fileName[], int ID, double x, double y, double z)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	P.setX(x);
	P.setY(y);
	P.setZ(z);

	Texture t;
	t.loadTexBMP(fileName, ID, addAlpha);

	id = ID;
}

void Billboard::setPosition(double x, double y, double z)
{
	P.setX(x);
	P.setY(y);
	P.setZ(z);
}

void Billboard::load(char fileName[], int ID)
{
	Texture t;
	t.loadTexBMP(fileName, ID, addAlpha);
}

void Billboard::draw(double size, bool BLENDING)
{
	// make sure the transparent part of the texture isn't drawn
	glEnable(GL_TEXTURE_2D);
	if (BLENDING)
		glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	// get the modelview matrix
	float matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

	// get the right and up vectors
	Vector r(matrix[0], matrix[4], matrix[8]);
	Vector u(matrix[1], matrix[5], matrix[9]);

	// select the texture
	glBindTexture(GL_TEXTURE_2D, id);

	glBegin(GL_QUADS);
		// bottom left corner
		glTexCoord2f(0.0, 0.0);
		Point bL = P + ( (size/2.0) * ( -1*u - r) );
		glVertex3f(bL.getX(), bL.getY(), bL.getZ());
					
		// bottom right corner
		glTexCoord2f(1.0, 0.0); 
		Point bR = P + ( (size/2.0) * ( -1*u + r) );
		glVertex3f(bR.getX(), bR.getY(), bR.getZ());

		// top right corner
		glTexCoord2f(1.0, 1.0); 
		Point tR = P + ( (size/2.0) * ( u + r) );
		glVertex3f(tR.getX(), tR.getY(), tR.getZ());
					
		// top left corner
		glTexCoord2f(0.0, 1.0);
		Point tL = P + ( (size/2.0) * ( u - r) );
		glVertex3f(tL.getX(), tL.getY(), tL.getZ());
	glEnd();

	glDisable(GL_ALPHA_TEST);
	if (BLENDING)
		glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}