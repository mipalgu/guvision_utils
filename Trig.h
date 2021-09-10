/* Mi-Pal 2005
** Trig.h
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
#ifndef TRIG_H
#define TRIG_H

double SIN_DEG(double deg);
#define COS_DEG(_x)		(SIN_DEG((_x) + 90))
#define TAN_DEG(_x)		(SIN_DEG(_x) / COS_DEG(_x))

#endif

