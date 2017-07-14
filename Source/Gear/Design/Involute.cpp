/*
 * Involute.cpp
 *
 *  Created on: 4. 5. 2017
 *      Author: martin
 */

/* Standard libary inclusions */
#include "../Design/Involute.h"

#include <cmath>

/* OpenCascade inclusions */
#include <TColgp_Array1OfPnt.hxx>
#include <Geom_BSplineCurve.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepAdaptor_Curve.hxx>

namespace Design
{
	Involute::Involute( const double BaseCircleRadius, const double OutsideCircleRadius, short Steps )
	{
		/* Involute data: List of points defining the curve */
		TColgp_Array1OfPnt InvolutePoints(0, Steps);

		/* TODO: What if BaseCircleRadius is bigger or equal to OutsideCirceRadius? --> Throw an exception here */

		/* Calculate generating parameter minimum and maximum values */
		double t_min ( 0.0 );
		double t_max ( std::sqrt( ( std::pow( OutsideCircleRadius, 2 ) - std::pow( BaseCircleRadius, 2 )  ) / std::pow( BaseCircleRadius, 2 ) ) );

		/* Calculate the difference between two iterations of generating parameter t */
		double t_delta ( (t_max - t_min) / Steps );

		/* x and y Cartesian coordinates */
		double x, y;

		/* Calculate x and y coordinates for all the iterations of generating parameter t */
		for( short i = 0; i <= Steps; i++ )
		{
			/* x = r_b + ( r_b*( cos(t) + t*sin(t) ) ) */
			x = BaseCircleRadius * ( std::cos( t_min + ( i * t_delta ) ) + ( t_min + ( i * t_delta ) ) * std::sin( t_min + ( i * t_delta ) ) );
			/* y = r_b ( sin(t) - t*cos(t) ) */
			y = BaseCircleRadius * ( std::sin( t_min + ( i * t_delta ) ) - ( t_min + ( i * t_delta ) ) * std::cos( t_min + ( i * t_delta ) ) );

			/* Add newly calculated value to the list of involute curve points */
			InvolutePoints.SetValue( i, gp_Pnt( x, y, 0.0 ) );
		}

		/* Create BSpline curve base on previously calculated points */
		Handle(Geom_BSplineCurve) InvoluteBSpline = GeomAPI_PointsToBSpline( InvolutePoints ).Curve();

		/* Create TopoDS_Shape out of Geom_BSplineCurve previously created */
		mInvoluteEdge = BRepBuilderAPI_MakeEdge( InvoluteBSpline, InvoluteBSpline->FirstParameter(), InvoluteBSpline->LastParameter() ).Edge();
	}

	#ifndef USE_STATIC_ENDPOINT_METHODS

	gp_Pnt Involute::getBaseEnd( void ) const
	{
		BRepAdaptor_Curve Curve( mInvoluteEdge );

		double Start = Curve.FirstParameter();
		gp_Pnt	StartPoint;
		gp_Vec	StartVector;

		Curve.D1( Start, StartPoint, StartVector );

		return( StartPoint );
	}

	gp_Pnt Involute::getOuterEnd( void ) const
	{
		BRepAdaptor_Curve Curve( mInvoluteEdge );

		double End = Curve.LastParameter();
		gp_Pnt	EndPoint;
		gp_Vec	EndVector;

		Curve.D1( End, EndPoint, EndVector );

		return( EndPoint );
	}

	#else

	gp_Pnt Involute::getBaseEnd( const TopoDS_Edge& Edge )
	{
		BRepAdaptor_Curve Curve( Edge );

		double Start = Curve.FirstParameter();
		gp_Pnt	StartPoint;
		gp_Vec	StartVector;

		Curve.D1( Start, StartPoint, StartVector );

		return( StartPoint );
	}

	gp_Pnt Involute::getOuterEnd( const TopoDS_Edge& Edge )
	{
		BRepAdaptor_Curve Curve( Edge );

		double End = Curve.LastParameter();
		gp_Pnt	EndPoint;
		gp_Vec	EndVector;

		Curve.D1( End, EndPoint, EndVector );

		return( EndPoint );
	}

	#endif

	Involute::operator TopoDS_Edge( void ) const
	{
		return( mInvoluteEdge );
	}
}
