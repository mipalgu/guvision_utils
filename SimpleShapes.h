#ifndef SIMPLE_SHAPES_H_
#define SIMPLE_SHAPES_H_

#include <cassert>
#include <cstdlib>
#include <cstddef>
#include <cctype>
#include <cmath>
#include <math_fnc.h>
#include <vector>
#include <typeinfo>
#include <gu_util.h>
//simple shapes classes

#pragma clang diagnostic push
//#pragma clang diagnostic warning "-W#warnings"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wunused-private-field"
#pragma clang diagnostic ignored "-Wc++98-compat"


#ifndef SQUARE
#define SQUARE(x) ((x)*(x))
#endif

struct Box {
    int lx;
    int rx;
    int by;
    int ty;
};

struct FieldLine {
	int startX;
	int startY;
	int endX;
	int endY;
	int startThickness;
	int endThickness;
	int length;
	double gradiant;
};

template <class T>
class GUPoint {
public:
        T x, y;
public:
	GUPoint<T>(): x(0), y(0) {}
	GUPoint(const GUPoint<T> &point): x(point.x), y(point.y) {}
        GUPoint(const char *str): x(0), y(0)    ///< C string constructor
        {                                       //   "(<xvalue>,<yvalue>)"
            if (!str || !*str) return;
            while (*str && *str != '-' && !isdigit(*str)) str++;
            if (!*str) return;
            x = static_cast<T>(atol(str++));

            while (*str && *str != ',') str++;
            if (!*str) return;
            if (!*++str) return;
            y = static_cast<T>(atol(str));
        }
    
    //Construct a point from a distance to the point and a direction
    //distance - distance to the point
    //direction - angle in degrees to the point, 0 degress is parallel to the y axis, +ve anticlockwise
    GUPoint(T v1, T v2, bool distDirection = false) {
        if(distDirection) {
            T distance = v1, direction = v2;
            x = static_cast<T>(cos((direction+90)*M_PI/180)*distance);
            y = static_cast<T>(sin((direction+90)*M_PI/180)*distance);
        }
        else {
            x = v1;
            y = v2;
        }
    }

	T Distance(const GUPoint<T> &point) const
        {
		return static_cast<T>(DISTANCE(this->x, this->y, point.x, point.y));
	}
    
    T Length() const {
        return static_cast<T>(DISTANCE(this->x, this->y, 0, 0));
    }
    
    //returns the angle from the origin to this point in degrees
    T angleFromOrigin() const {
        if(Length() == 0)
            return 0;
        return static_cast<T>(acos(static_cast<double>(x/Length()))*180.0/M_PI);
    }

	GUPoint<T> Unit() const
        {
		if(this->x == 0 && this->y == 0)
			return *this;
		else
			return *this / GUPoint::Length(GUPoint<T>(0,0), *this);
	}

	GUPoint UnitFromPoint(const GUPoint<T> &p) const { return (*this - p).Unit(); }

	static inline T Length(const GUPoint<T> &a, const GUPoint<T> &b) 
        {
		return  T(  sqrt(SQUARE(a.x-b.x) + SQUARE(a.y-b.y)) );
	}

	GUPoint<T> operator=(const GUPoint<T> &a)
        {
		this->x = a.x;
		this->y = a.y;
		return *this;
	}
	
	template<class U>
	GUPoint<T> operator=(const GUPoint<U> &a) {
		this->x = static_cast<T>(a.x);
		this->y = static_cast<T>(a.y);
		return *this;
	}
        bool operator==(const GUPoint<T> &a) const
        {
            if(this->x == a.x && this->y == a.y)
                return true;
            return false;
        }
	GUPoint<T> operator*(T a) const { return GUPoint<T>(x*a, y*a); }
	GUPoint<T> operator/(T a) const { return GUPoint<T>(x/a, y/a); }
	GUPoint<T> operator+(const GUPoint<T> &p) const { return GUPoint<T>(x+p.x, y+p.y); }
	GUPoint<T> operator-(const GUPoint<T> &p) const { return GUPoint<T>(x-p.x, y-p.y); }
	GUPoint<short> toShort() const { return GUPoint<short>(short(x), short(y)); }
};

/// super class for other shapes
class SimpleShape {
public:
        SimpleShape() {}
        SimpleShape(const SimpleShape &shape) { shape.Copy(this); }
        SimpleShape &operator=(const SimpleShape &shape) { shape.Copy(this); return *this; }
	virtual short shapePointIntersection(const GUPoint<short> &p, GUPoint<short> *pIntersection) const = 0;
	virtual void Copy(SimpleShape *shape) const = 0;
        virtual bool insideShape(const GUPoint<int> &point) const = 0;
	virtual ~SimpleShape() { }
	virtual int Area() = 0;
	virtual std::vector<GUPoint<short> > intersections(SimpleShape&) { return std::vector<GUPoint<short> >();}
};

class SimpleCircle: public SimpleShape
{
public:
	SimpleCircle(): SimpleShape(), m_dRadius(-1), m_Center(9999, 9999) {}
        SimpleCircle(GUPoint<short> center, double radius) {
            m_dRadius = radius;
            m_Center = center;
        }

        SimpleCircle(short x, short y, double radius) {
            m_dRadius = radius;
            m_Center = GUPoint<short>(x, y);
        }

        SimpleCircle(const SimpleCircle &shape): SimpleShape(shape) {m_dRadius = shape.m_dRadius; m_Center = shape.m_Center;}
        //SimpleCircle(const SimpleShape &shape): SimpleShape(shape) {}
	SimpleCircle(const GUPoint<short> *p1, const GUPoint<short> *p2, const GUPoint<short> *p3) {	// p1, p2, p3 are co-planar
		FindCircle(p1, p2, p3);
	}
        SimpleCircle &operator=(const SimpleCircle &shape) { shape.Copy(this); return *this; }
    virtual short shapePointIntersection(const GUPoint<short> &p, GUPoint<short> *pIntersection) const OVERRIDE {
		if(m_dRadius <= 0)
			return -1;
		if(pIntersection != NULLPTR)
			*pIntersection = m_Center + p.UnitFromPoint(m_Center) * short(m_dRadius);
		short len = GUPoint<short>::Length(p, m_Center);
		if(len >= m_dRadius)
			//len -= m_dRadius;
			len = static_cast<short>(len-m_dRadius);
		else
			len = static_cast<short>(m_dRadius - len);
		return len;
	}
        virtual bool insideShape(const GUPoint<int> &) const OVERRIDE { assert(false); }
	virtual void Copy(SimpleShape *circle) const OVERRIDE {
		(static_cast<SimpleCircle *>(circle))->m_Center = this->m_Center;
		(static_cast<SimpleCircle *>(circle))->m_dRadius = this->m_dRadius;
	}
	void FindCircle(const GUPoint<short> *p1, const GUPoint<short> *p2, const GUPoint<short> *p3) {
		this->m_dRadius=-1;		// error checking

		GUPoint<short> pt1=*p1;	GUPoint<short> pt2=*p2;	GUPoint<short> pt3=*p3;

		if (!this->IsPerpendicular(&pt1, &pt2, &pt3) )				this->CalcCircle(&pt1, &pt2, &pt3);
		else if (!this->IsPerpendicular(&pt1, &pt3, &pt2) )		this->CalcCircle(&pt1, &pt3, &pt2);
		else if (!this->IsPerpendicular(&pt2, &pt1, &pt3) )		this->CalcCircle(&pt2, &pt1, &pt3);
		else if (!this->IsPerpendicular(&pt2, &pt3, &pt1) )		this->CalcCircle(&pt2, &pt3, &pt1);
		else if (!this->IsPerpendicular(&pt3, &pt2, &pt1) )		this->CalcCircle(&pt3, &pt2, &pt1);
		else if (!this->IsPerpendicular(&pt3, &pt1, &pt2) )		this->CalcCircle(&pt3, &pt1, &pt2);
		else {
			//The three pts are perpendicular to axis\n
			this->m_dRadius=-1;
		}
	}
	GUPoint<short> GetCenter() const { return m_Center; }
	short GetRadius() const { return short( m_dRadius) ; }
	int Area() OVERRIDE {
		return int(PI*GetRadius()*GetRadius());
	}
	void setCenter(GUPoint<short> center) {
		m_Center = center;
	}
	
	void setRadius(double radius) {
		m_dRadius = radius;
	}


private:
	double CalcCircle(GUPoint<short> *pt1, GUPoint<short> *pt2, GUPoint<short> *pt3) {
		double yDelta_a= pt2->y - pt1->y;
		double xDelta_a= pt2->x - pt1->x;
		double yDelta_b= pt3->y - pt2->y;
		double xDelta_b= pt3->x - pt2->x;
		
		if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
			this->m_Center.x= short(0.5*(pt2->x + pt3->x));
			this->m_Center.y= short(0.5*(pt1->y + pt2->y));
			this->m_dRadius= GUPoint<short>::Length(this->m_Center, *pt1);// calc. radius
			
			return this->m_dRadius;
		}
		
		// IsPerpendicular() assure that xDelta(s) are not zero
		double aSlope=yDelta_a/xDelta_a; //
		double bSlope=yDelta_b/xDelta_b;
		if (fabs(aSlope-bSlope) <= 0.000000001){	// checking whether the given points are colinear.
			this->m_dRadius = -1;
			return -1;
		}

		double cx, cy, r;
		cx = (aSlope*bSlope*(pt1->y - pt3->y) + bSlope*(pt1->x + pt2 ->x)
			- aSlope*(pt2->x+pt3->x) )/(2.0* (bSlope-aSlope) );
		cy = -1.0*(cx - (pt1->x+pt2->x)/2.0)/aSlope +  (pt1->y+pt2->y)/2.0;
		r = GUPoint<double>::Length(GUPoint<double>(cx, cy), GUPoint<double>(static_cast<double>(pt1->x), static_cast<double>(pt1->y)));
		// calc center
		this->m_Center.x= short(cx + 0.5);
		this->m_Center.y = short(cy + 0.5);
		
		this->m_dRadius= r; // calc. radius

		//fprintf(stderr, "cx %f cy %f r %f\n", cx, cy, r);

		return this->m_dRadius;
	}
	// Check the given point are perpendicular to x or y axis
	bool IsPerpendicular(const GUPoint<short> *pt1, const GUPoint<short> *pt2, const GUPoint<short> *pt3) {
		double yDelta_a= pt2->y - pt1->y;
		double xDelta_a= pt2->x - pt1->x;
		double yDelta_b= pt3->y - pt2->y;
		double xDelta_b= pt3->x - pt2->x;

		// checking whether the line of the two pts are vertical
		if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
			return false;
		}

		if (fabs(yDelta_a) <= 0.0000001){
			return true;
		}
		else if (fabs(yDelta_b) <= 0.0000001){
			return true;
		}
		else if (fabs(xDelta_a)<= 0.000000001){
			return true;
		}
		else if (fabs(xDelta_b)<= 0.000000001){
			return true;
		}
		else return false ;
	}
	
	double m_dRadius;
	GUPoint<short> m_Center;
        int32_t _padding;
};

class SimpleLine: public SimpleShape
{
public:
	SimpleLine(): SimpleShape(), start(0, 0), end(0, 0) {}
        SimpleLine(const SimpleLine &line): SimpleShape(), start(line.start), end(line.end) {}
	SimpleLine(const GUPoint<short> *p1, const GUPoint<short> *p2): SimpleShape(), start(*p1), end(*p2) {}
	SimpleLine(const GUPoint<short> &p1, const GUPoint<short> &p2): SimpleShape(), start(p1), end(p2) {}
        SimpleLine &operator=(const SimpleLine &shape) { shape.Copy(this); return *this; }

	short GetLength() const { return GUPoint<short>::Length(start, end); }
	double length() const { return GUPoint<double>::Length(GUPoint<double>(start.x, start.y), GUPoint<double>(end.x, end.y)); }
    
    GUPoint<short> UnitVector() const {
        GUPoint<short> result = GUPoint<short>(end.x - start.x, end.y - start.y);
        return result/short(round(length()));
    }

        virtual bool insideShape(const GUPoint<int> &) const OVERRIDE { assert(false); }

	//calcuates the shortest distance between the given point and this line
	//pIntersection the point on the line closest to the given point
	//return the shortest distance
	short shapePointIntersection(const GUPoint<short> &p, GUPoint<short> *pIntersection) const OVERRIDE
        {
		if(pIntersection != NULLPTR) {
            SimpleLine direction = this->normalToOrigin()+p;
            *pIntersection = this->lineIntersection(direction)[0];
            //*pIntersection = dotLineIntersection(p.x, p.y, start.x, start.y, end.x, end.y);
            return GUPoint<short>::Length(p, *pIntersection);
		}
		else
                {
			double normalLength = sqrt(SQUARE(end.x - start.x) + SQUARE(start.y - end.y));
                    if(normalLength < 0.01) {
                        return GUPoint<short>::Length(p, start);
                    }
			return short(abs((p.x - start.x) * (end.y - start.y) - (p.y - start.y)*(end.x - start.x))/normalLength);
		}
	}
    
    //calculates the shortest distanace from the provided point to this line segment
    //p  the point to calculate the distance from
    //pIntersection - set to the point on the line segment that is closest if not null
    short distanceToLineSegment(const GUPoint<short> &p, GUPoint<short> *pIntersection = NULLPTR) const {
        short d = shapePointIntersection(p, pIntersection);
        if(p.Distance(start) < d) {
            if(pIntersection != NULLPTR)
                *pIntersection = start;
        }
        
        if(p.Distance(end) < d) {
            if(pIntersection != NULLPTR)
                *pIntersection = end;
        }
        return d;
    }
    
    //calculates the shortest distanace from the origin to this line segment
    //pIntersection - set to the point on the line segment that is closest if not null
    short distanceToLineSegment(GUPoint<short> *pIntersection = NULLPTR) const {
        return distanceToLineSegment(GUPoint<short>(0,0), pIntersection);
    }
	
	int Area() OVERRIDE {
		return 0; //TODO, needs four points.
	}
	
	static GUPoint<short> dotLineIntersection(short x, short y, short lx0, short ly0, short lx1, short ly1) {
		if(!(lx1 - lx0))
			return GUPoint<short>(lx0, y);
		else if(!(ly1 - ly0))
			return GUPoint<short>(x, ly0);
		double tg = -1 / ((ly1 - ly0) / static_cast<double>((lx1 - lx0)));
		short left = short((lx1 * (x * tg - y + ly0) + lx0 * (x * - tg + y - ly1)) / (tg * (lx1 - lx0) + ly0 - ly1));
		return GUPoint<short>(left, short(tg * left - tg * x + y));
	}
	
	virtual void Copy(SimpleShape *Line) const OVERRIDE
        {
		static_cast<SimpleLine *>(Line)->start = this->start;
		static_cast<SimpleLine *>(Line)->end= this->end;
	}
	
	float Gradiant() const
        {
		if(end.x == start.x)
			return (end.y - start.y)*100.0f;
		return static_cast<float>(end.y - start.y)/(end.x - start.x);
	}

	/**
	 * Gives the angle of the line
	 * @return angle between 0 and PI
	 */
	double angle() const {
		if(start.y <= end.y)
			return acos((end.x - start.x)/length());
		else
			return acos((start.x - end.x)/length());
	}
	
    int angleToX() const {
        return static_cast<int>(atan2(end.y- start.y, end.x - start.x)*180/M_PI);
    }
    
	/**
	 * @return the point whose y value is less
	 */
	GUPoint<short> pointWithSmallestY() const {
		if(start.y < end.y)
			return start;
		else
			return end;
	}
	
	/**
	 * @return the point whose y value is greater
	 */
	GUPoint<short> pointWithLargestY() const {
		if(start.y > end.y)
			return start;
		else
			return end;
	}

	/**
	 * @return the point whose y value is closest to 0
	 */
	GUPoint<short> lowestPoint() const {
		if(start.y < end.y)
			return start;
		else
			return end;
	}
	
	/**
	 * @return the point whose y value is furtherest to 0
	 */
	GUPoint<short> highestPoint() const {
		if(start.y > end.y)
			return start;
		else
			return end;
	}
	
	/**
	 * @return the point whose x value is closest to 0
	 */
	GUPoint<short> leftPoint() const {
		if(start.x < end.x)
			return start;
		else
			return end;
	}
	
	/**
	 * @return the point whose x value is furtherest to 0
	 */
	GUPoint<short> rightPoint() const {
		if(start.x > end.x)
			return start;
		else
			return end;
	}
	/**
	 * Extrapolate point on line from given x
     * @param x The x coordinate
     * @return A point that lies on the line with the given x value
     */
	GUPoint<short> pointFromX(short x) {
        GUPoint<short> a = leftPoint();
        GUPoint<short> b = rightPoint();
        double slope = static_cast<double>(b.y - a.y) / static_cast<double>(b.x - a.x);
        short y = static_cast<short>(a.y + (x - a.x) * slope);
		return GUPoint<short>(x, y);
	}
	/**
	 * Extrapolate point on line from given y
     * @param y The y coordinate
     * @return A point that lies on the line with the given y value
     */
	GUPoint<short> pointFromY(short y) {
        GUPoint<short> a = lowestPoint();
        GUPoint<short> b = highestPoint();
        double slope = static_cast<double>(b.x - a.x) / static_cast<double>(b.y - a.y);
        short x = static_cast<short>(a.x + (y - a.y) * slope);
		return GUPoint<short>(x, y);
	}
	
	std::vector<GUPoint<short> > intersections(SimpleShape& shape) OVERRIDE {
		if(typeid(shape) == typeid(SimpleLine))
			return lineIntersection(static_cast<SimpleLine&>(shape));
		else
			return SimpleShape::intersections(shape);
	}
    
private:
    bool ccw(GUPoint<short> A, GUPoint<short> B, GUPoint<short> C) {
        return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x);
    }
public:
    bool intersects(SimpleLine line) {
        GUPoint<short> A = this->start;
        GUPoint<short> B = this->end;
        GUPoint<short> C = line.start;
        GUPoint<short> D = line.end;
        return ccw(A,C,D) != ccw(B,C,D) && ccw(A,B,C) != ccw(A,B,D);
    }

	
	/**
	 * Calculate the intersection of this line with the given line
     * @param l The line that this line intersects with
     * @return The point of intersection
     */
	std::vector<GUPoint<short> > lineIntersection(SimpleLine& l) const {
		int a1 = end.y - start.y, a2 = l.end.y - l.start.y;
		int b1 = start.x - end.x, b2 = l.start.x - l.end.x;
		int c1 = a1*start.x+b1*start.y, c2 = a2*l.start.x+b2*l.start.y;
		
		std::vector<GUPoint<short> > res;
		
		int det = a1*b2 - a2*b1;
		if(a1*b2 - a2*b1 == 0) {
			return res;
		}
		res.push_back(GUPoint<short>(static_cast<short>((b2*c1-b1*c2)/det), static_cast<short>((a1*c2-a2*c1)/det)));
		
		return res;
	}
	
	/**
	 * Calculates a line normal to the current line that passes through the origin
     * @return The newly calculated line 
     */
	SimpleLine normalToOrigin() const {
		double a = angle();
		if(a >= M_PI_2)
			a-=M_PI_2;
		else 
			a+=M_PI_2;
		SimpleLine normal(GUPoint<short>(0,0), GUPoint<short>(static_cast<short>((cos(a)*100)), static_cast<short>((sin(a)*100))));
		GUPoint<short> intersection = lineIntersection(normal)[0];
		if(intersection.x == 0 && intersection.y == 0)
			return normal;
		return SimpleLine(GUPoint<short>(0,0), lineIntersection(normal)[0]);
	}
        
        /**
         * Find the point a certain distance from the start point along the line
         * @param distance from the start of the line
         * @return The point lying on this line
         */
        GUPoint<short> distanceAlongeLine(int distance) {
            double t = distance/this->length();
            double x = (1-t)*start.x + t*end.x;
            double y = (1-t)*start.y + t*end.y;
            return GUPoint<short>(short(x),short(y));
        }

	/**
	 * SimpleLine clockwise rotation around the center point
     * Assumes screen coords (0, 0) in the top left etc..
     * @return The newly rotated line 
     */
    SimpleLine rotated(double radians) {
        double s = sin(radians);
        double c = cos(radians);

        //line center
        double cx = static_cast<double>((start.x + end.x) / 2.0f);
        double cy = static_cast<double>((start.y + end.y) / 2.0f);

        double nsx = c * (start.x - cx) - s * (start.y - cy) + cx;
        double nsy = s * (start.x - cx) - c * (start.y - cy) + cy;

        double nex = c * (end.x - cx) - s * (end.y - cy) + cx;
        double ney = s * (end.x - cx) - c * (end.y - cy) + cy;

        //rounding newly rotated points, rather than down-casting them.
        return SimpleLine(
            GUPoint<short>(
                static_cast<short>(round(nsx)),
                static_cast<short>(round(nsy))
                ),
            GUPoint<short>(
                static_cast<short>(round(nex)),
                static_cast<short>(round(ney))
                ));
    }
	
	//operators to translate a line
	SimpleLine operator+(GUPoint<short> p) {
		SimpleLine r;
		r.start = this->start + p;
		r.end = this->end + p;
		return r;
	}
	
	SimpleLine operator-(GUPoint<short> p) {
		SimpleLine r;
		r.start = this->start - p;
		r.end = this->end - p;
		return r;
	}

	GUPoint<short> start, end;
};


class SimpleRectangle: public SimpleShape
{
public:
        SimpleRectangle(): SimpleShape(), topLeft(0, 0), bottomRight(0, 0) {}
        SimpleRectangle(const SimpleRectangle &rect): SimpleShape(), topLeft(rect.topLeft), bottomRight(rect.bottomRight) {}
        SimpleRectangle(int left, int right, int top, int bottom)
        {
                int tmp;
                if(left >  right)
                {
                        tmp = right;
                        right = left;
                        left = tmp;
                }
                if(bottom >  top)
                {
                        tmp = bottom;
                        bottom = top;
                        top = tmp;
                }
                topLeft.x = left;
                topLeft.y = top;
                bottomRight.x = right;
                bottomRight.y = bottom;
        }
	
	bool Overlaps(const SimpleRectangle & r) {
		return (r.left() < right() && r.right() > left() &&
				r.top() > bottom() && r.bottom() < top() );
	}
	
	bool Intersection(const SimpleRectangle& r, SimpleRectangle& intersection) {
		if(!Overlaps(r))
			return false;
		intersection.setLeft(MAX(left(), r.left()));
		intersection.setRight(MIN(right(), r.right()));
		intersection.setBottom(MAX(bottom(), r.bottom()));
		intersection.setTop(MIN(top(), r.top()));
		return true;
	}
	
	SimpleRectangle Union(const SimpleRectangle& r) {
		SimpleRectangle res(std::min(left(), r.left()), std::max(right(), r.right()),
							std::min(bottom(), r.bottom()), std::max(top(), r.top()));
		return res;
	}
		
		SimpleRectangle& operator=(const SimpleRectangle& r) {
			topLeft = r.topLeft;
			bottomRight = r.bottomRight;
			return *this;
		}
		
		int Area() OVERRIDE {
			return abs(left()-right())*abs(top()-bottom());
		}
	
	int Width() {
		return right() - left();
	}
	
	int Height() {
		return top() - bottom();
	}
	
	GUPoint<short> Center() {
		GUPoint<short> center;
		center.x = static_cast<short>((right()+left())/2);
		center.y = static_cast<short>((top()+bottom())/2);
		return center;
	}
	
	//returns the distance between the closest sides of the two rectangles
	int DistannceTo(const SimpleRectangle& rec) {
		//printf("FIXME! DistanceTo This calculation is incorrect");
		if(Overlaps(rec))
			return 0;
		int min = abs(rec.right() - left());
		min  = MIN(min, abs(right() - rec.left()));
		min  = MIN(min, abs(bottom() - rec.top()));
		min  = MIN(min, abs(rec.bottom() - top()));
		return min;
	}
    
        virtual void Copy(SimpleShape *rectangle) const OVERRIDE
        {
                static_cast<SimpleRectangle *>(rectangle)->bottomRight = bottomRight;
                static_cast<SimpleRectangle *>(rectangle)->topLeft = topLeft;
        }

        virtual short shapePointIntersection(const GUPoint<short> &, GUPoint<short> *) const OVERRIDE { assert(false); }

        virtual bool insideShape(const GUPoint<int> &point) const OVERRIDE
        {
                return (point.x > topLeft.x && point.x < bottomRight.x) &&
                       (point.y < topLeft.y && point.y > bottomRight.y);
        }
    
        int left() const { return topLeft.x; }
        int right() const { return bottomRight.x; }
        int top() const { return topLeft.y; }
        int bottom() const { return bottomRight.y; }
	void setLeft(int left) { topLeft.x = left; }
	void setRight(int right) {bottomRight.x = right; }
	void setTop(int top) { topLeft.y = top; }
	void setBottom(int bottom) {bottomRight.y = bottom; }

private:
        GUPoint<int> topLeft, bottomRight;
};

#pragma clang diagnostic pop

#endif
