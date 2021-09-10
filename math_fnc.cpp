/* Mi-Pal 2005
** math_fnc.cpp
** Author: Nathan Lovell
********************************************************
** This file is copyright to the authors.
** It formed part of the Mi-Pal 2005 entry in
** the Robocup Legged league
**************************************************************
** This code is released under GPL V2.0 (see license.txt)
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
** MA  02111-1307  USA
** Note: No warantee of any kind is associated with this code.
**************************************************************

*/
#include "math_fnc.h"
	
double NORMALIZE_ANGLE(double x)					
{
	while (x < (-1 * PI))	x += (2 * PI); 
	while (x > PI)			x -= (2 * PI);
	return x;
}

void TRANSLATE_POINT(double &pointX, double &pointY, double translateX, double translateY)
{
	pointX -= translateX;
	pointY -= translateY;
}

void ROTATE_POINT(double &pointX, double &pointY, double rotateAngle, double rotateAboutPointX /*= 0*/, double rotateAboutPointY /*= 0*/)
{
	double cosTheta = cos(rotateAngle);
	double sinTheta = sin(rotateAngle);

	TRANSLATE_POINT(pointX, pointY, rotateAboutPointX, rotateAboutPointY);
	double newX = cosTheta * pointX - sinTheta * pointY;
	double newY = sinTheta * pointX + cosTheta * pointY;
	pointX = newX;
	pointY = newY;
	TRANSLATE_POINT(pointX, pointY, -1 * rotateAboutPointX, -1 * rotateAboutPointY);
}

void ROTATE_IMAGE_POINT(double &pointX, double &pointY, double rotateAngle, int imgY)
{
	double oldAngle = atan((imgY - pointY) / pointX);
	if (pointX < 0) oldAngle += PI;
	double newAngle = oldAngle + rotateAngle;
	double r = SQRT(SQUARE(pointX) + SQUARE(imgY - pointY));

	pointX = r * cos(newAngle);
	pointY = imgY - (r * sin(newAngle));
}

int ROUND(double d)
{
	if ((d - static_cast<int>(d)) > 0.5)
		return static_cast<int>(d) + 1;
	else
		return static_cast<int>(d);
}

double SQ_POLAR_DISTANCE(double r1, double theta1, double r2, double theta2)
{
	double ang = MAX(theta1, theta2) - MIN(theta1, theta2);
	double cang = cos(ang);
	double dist = SQUARE(r1) + SQUARE(r2) + (2 * r1 * r2 * cang);
	return dist;
}
