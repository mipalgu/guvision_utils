/* Mi-Pal 2005
** math_fnc.h
** Author: Nathan Lovell
** Description: Various mathematical definitions and functions
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
#ifndef MATH_FNC_H
#define MATH_FNC_H

#include <math.h>
#include <sys/param.h>
#include "Trig.h"

#define PI		3.141592
#define SQRT2	1.414213

#define DEG_TO_RAD(x)					((double)((x) * PI) / 180)
#define RAD_TO_MICRO(x)					((long) ((x) * 1000000))
#define DEG_TO_MICRO(x)					(RAD_TO_MICRO(DEG_TO_RAD(x)))
#define RAD_TO_DEG(x)					((double)((x) * 180) / PI)
#define MICRO_TO_RAD(x)					((double)(x) / 1000000)
#define MICRO_TO_DEG(x)					(RAD_TO_DEG(MICRO_TO_RAD(x)))
#define MICRO_TO_M(x)					((double)(x) / 1000000)
#define MICRO_TO_CM(x)					((double)(x) / 100000)

// WHAT????
//#define CARTESION_TO_THETA(x, y, rel)	(NORMALIZE_ANGLE((atan2((y), (x)) - (PI / 2)) - rel))

#define CARTESION_TO_THETA(x, y, rel)   (atan2((y),(x)))
#define CARTESION_TO_R(x, y)			((sqrt(SQUARE(x) + SQUARE(y))))
// DO NOT USE ON THE ROBOT. FOR VISION USE ONLY
#define POLAR_TO_X(r, t)				((r) * -1 * sin(t))
#define POLAR_TO_Y(r, t)	            ((r) * cos(t))

#define SQUARE(x)						((x) * (x))	
#define SQRT							sqrt
#define SQ_DISTANCE(x1, y1, x2, y2)		(SQUARE((x1)- (x2)) + SQUARE((y1) - (y2)))
#define DISTANCE(x1, y1, x2, y2)		(sqrt(static_cast<double>(SQ_DISTANCE(x1, y1, x2, y2))))
#define SQ_DISTANCE3(x1, y1, z1, x2, y2, z2)	(SQUARE((x1)- (x2)) + SQUARE((y1) - (y2))  + SQUARE((z1) - (z2)))
#define DISTANCE3(x1, y1, z1, x2, y2, z2)		(sqrt((double)SQ_DISTANCE3(x1, y1, z1, x2, y2, z2)))
#define MAN_DISTANCE(x1, y1, x2, y2)	(ABS((x1) - (x2)) + ABS((y1) - (y2)))
#ifndef MAX
#define MAX(a, b)						(((a) > (b)) ? (a) : (b))
#define MIN(a, b)						(((a) < (b)) ? (a) : (b))	
#endif
#ifndef ABS
#define ABS(a)							(((a) < 0) ? (-1 * (a)) : (a))
#endif
#define EFFECTIVE_ZERO(x)				(ABS(x) < 0.0001 ? true : false)

#define IN_ORDERED_INTERVAL(a, b, c)	((a <= b) && (b <= c))
#define IN_INTERVAL(a, b, c)			((IN_ORDERED_INTERVAL(a, b, c)) || (IN_ORDERED_INTERVAL(c, b, a)))

double NORMALIZE_ANGLE(double x);
void TRANSLATE_POINT(double &pointX, double &pointY, double translateX, double translateY);
void ROTATE_POINT(double &pointX, double &pointY, double rotateAngle, double rotateAboutPointX = 0, double rotateAboutPointY = 0);
void ROTATE_IMAGE_POINT(double &pointX, double &pointY, double rotateAngle, int imgY);
int ROUND(double d);

#define POLAR_DISTANCE(r1, theta1, r2, theta2) (SQRT(SQ_POLAR_DISTANCE((r1), (theta1), (r2), (theta2))))
double SQ_POLAR_DISTANCE(double r1, double theta1, double r2, double theta2);

#define COSINE_RULE_ANGLE(_a, _b, _c)									 (acos((SQUARE(_b) + SQUARE(_c) - SQUARE(_a)) / (2 * (_b) * (_c))))
#define COSINE_RULE_ANGLE_SQ(_b, _c, _sqa, _sqb, _sqc)		 (acos(((_sqb) + (_sqc) - (_sqa)) / (2 * (_b) * (_c))))											// Use this if the squares are already precalculated
#define COSINE_RULE_SIDE(_A, _b, _c)									 (SQRT(SQUARE(_b) + SQUARE(_c) - (2 * (_b) * (_c) * cos(_A)))				// TODO WARNING: NOT TESTED
#define SINE_RUILE_ANGLE(_a, _A, _b)									 (((_b) * sin((_A))) / (_a))																			// TODO WARNING: NOT TESTED
#define SINE_RULE_SIDE(_a, _A, _B)										 (((_a) * sin((_B))) / sin((_A)))																	// TODO WARNING: NOT TESTED

#ifdef __LINUX__
      #define FINITE finite
#endif
#ifdef __WIN32__
      #define FINITE _finite
#endif

#define SIN(_x)	(SIN_DEG(RAD_TO_DEG(_x)))
#define COS(_x)	(COS_DEG(RAD_TO_DEG(_x)))
#define TAN(_x) (TAN_DEG(RAD_TO_DEG(_x)))
      
#endif // MATH_FNC_H
