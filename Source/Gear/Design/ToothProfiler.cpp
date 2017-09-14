/*
 * ToothProfile.cpp
 *
 *  Created on: 4. 5. 2017
 *      Author: martin
 */

/* Standard library inclusions */
#include <iostream>

/* OpenCascade inclusions */
#include <gp.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_Ax1.hxx>
#include <gp_Trsf.hxx>
#include <gp_Pln.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_BSplineCurve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeShape.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_WireError.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#if 0
#include <BRepOffsetAPI_MakePipeShell.hxx>
#endif
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <StdFail_NotDone.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <AIS_InteractiveContext.hxx>
#include <ChFi2d_FilletAPI.hxx>

#if 0
#include <Geom2d_TrimmedCurve.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <gp_Lin2d.hxx>
#endif

/* Project specific inclusions */
#include "Parameter/ParameterContainer.h"
#include "Component/Exception.h"

#include "../Design/ToothProfiler.h"

#include "../Design/Exception.h"
#include "../Design/Equations.h"
#include "../Design/Involute.h"

namespace Design
{
	template<typename GEAR_TYPE>
	std::unique_ptr<TopoDS_Wire> ToothProfiler<GEAR_TYPE>::operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const
	{
		return( std::move( ToothProfile<GEAR_TYPE, ToothProfileTag>()( Parameters ) ) );
	}

	gp_Pnt calcPointOnCircle( const Core::Parameter<si::length, double> & Diameter, const Core::Parameter<si::plane_angle, double> & Angle )
	{
		return( gp_Pnt( ( (Diameter.value() / 2.0) * std::cos( Angle.value() ) ) , ( (Diameter.value() / 2.0) * std::sin( Angle.value() ) ) , 0.0 ) );
	}

	template<typename GEAR_TYPE>
	GEAR_EXPORT std::unique_ptr<TopoDS_Wire> ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Straight>::operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const
	{
		std::cout << "Creating STRAIGHT tooth profile." << std::endl;

		TopoDS_Wire tToothProfile;

		return( std::make_unique<TopoDS_Wire>( tToothProfile ) );
	}

	template<typename GEAR_TYPE>
	GEAR_EXPORT std::unique_ptr<TopoDS_Wire> ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Involute>::operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const
	{
		std::cout << "Creating INVOLUTE tooth profile." << std::endl;

		/* Local tooth profile variable used during the construction */
		BRepBuilderAPI_MakeWire ToothProfileWireMaker;

		Core::Parameter<si::plane_angle, double> ProfileStartAngle( - ( ( (* Parameters->get<GearParameterTagCollection::ANGULAR_TOOTH_WIDTH, Equations<GEAR_TYPE>>() ) - (* Parameters->get<GearParameterTagCollection::TOOTH_BASE_ANGLE, Equations<GEAR_TYPE>>() ) ) / 2.0 ) );
		Core::Parameter<si::plane_angle, double> ProfileEndAngle( ProfileStartAngle + (* Parameters->get<GearParameterTagCollection::ANGULAR_TOOTH_WIDTH, Equations<GEAR_TYPE>>() ) );

		/* ========== BOTTOM LAND SECTION 1 ========== */
		/* P1 -----------------> Arc -----------------> P2 */

		/* Calculate point P1 where the profile starts */
		gp_Pnt P1 = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::ROOT_DIAMETER, Equations<GEAR_TYPE>>() ), ProfileStartAngle );

		/* Calculate one bottom land point to define the arc of root circle diameter */
		gp_Pnt BottomLandPoint1 = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::ROOT_DIAMETER, Equations<GEAR_TYPE>>() ), ProfileStartAngle / 2.0 );

		/* Point P2 lays on x-axis on root circle */
		gp_Pnt P2 ( ( Parameters->get<GearParameterTagCollection::ROOT_DIAMETER, Equations<GEAR_TYPE>>()->value() / 2.0 ) , 0.0 , 0.0 );

		/* ... create bottom land section */
		TopoDS_Edge BottomLandSection1 = BRepBuilderAPI_MakeEdge( GC_MakeArcOfCircle( P1 , BottomLandPoint1, P2 ).Value() );

		/* ========== TOOTH FACE SECTION 1 ========== */
		/* P2 -----------------> Involute Curve -----------------> P3 */
		/* Tooth face is defined by involute curve. */
		TopoDS_Edge ToothFaceSection1 = Involute( ( Parameters->get<GearParameterTagCollection::BASE_DIAMETER, Equations<GEAR_TYPE>>()->value() / 2.0 ), ( Parameters->get<GearParameterTagCollection::OUTSIDE_DIAMETER, Equations<GEAR_TYPE>>()->value() / 2.0 ) );

		/* Involute section begins with point P1 and ends with P2 */
		gp_Pnt P3 = Involute::getBaseEnd( ToothFaceSection1 );
		gp_Pnt P4 = Involute::getOuterEnd( ToothFaceSection1 );

		/* ========== TOOTH FLANK SECTION 1 ========== */
		/* P2 -----------------> Straight line -----------------> P3 */
		TopoDS_Edge ToothFlankSection1 = BRepBuilderAPI_MakeEdge( P2, P3 );

		/* ========== BOTTOM LAND FILLET SECTION 1 ========== */
		/* Let's define a plane where both edges lay and where the fillet shall be created as well */
		/* Construct a plane with origin at [0,0,0] and the normal vector equal to z-axis */
		gp_Pln ToothProfilePlane( gp::Origin(), gp::DZ() );

		/* Create fillet section edge */
		TopoDS_Edge BottomLandFilletSection1;

		/* Create 2D fillet builder */
		ChFi2d_FilletAPI BottomLandFillet1( BottomLandSection1, ToothFlankSection1, ToothProfilePlane );

		/* Perform the fillet construction and check for the result */
		if( BottomLandFillet1.Perform( Parameters->get<GearParameterTagCollection::FILLET_RADIUS, Equations<GEAR_TYPE>>()->value() ) != true)
		{
			/* No fillet solution found */
			BOOST_THROW_EXCEPTION( Component::Exception::Design::ModelConstructionFailed() << Core::Exception::Message( "Fillet construction failed." ) );
		}

		/* The fillet is constructed, both original edges are modified */
		BottomLandFilletSection1 = BottomLandFillet1.Result( P2, BottomLandSection1, ToothFlankSection1 );

		/* ========== TOOTH FACE SECTION 2 ========== */
		/* P5 -----------------> Involute Curve -----------------> P6 */
		/* The other involute section is mirrored and rotated copy of the first involute curve */
		/* ... so prepare the transformations */
		gp_Trsf	InvoluteMirrorTransformation;
		gp_Trsf	InvoluteRotationTransformation;

		/* ... setup the transformations */
		/* The original involute shall be mirrored by x-axis */
		InvoluteMirrorTransformation.SetMirror( gp::OX() );
		/* Mirrored involute shall be later on rotated by dedendum angle which defines the angular distance between
		 * the two involutes at the base circle */
		InvoluteRotationTransformation.SetRotation( gp::OZ(), Parameters->get<GearParameterTagCollection::TOOTH_BASE_ANGLE, Equations<GEAR_TYPE>>()->value() );

		/* Apply both transformations in the right order to create the second involute side */
		BRepBuilderAPI_Transform MirrorTransformer( ToothFaceSection1, InvoluteMirrorTransformation );
		BRepBuilderAPI_Transform RotationTransformer( TopoDS::Edge( MirrorTransformer.Shape() ), InvoluteRotationTransformation );

		/* ... and finally the second involute section is born */
		TopoDS_Edge ToothFaceSection2 = TopoDS::Edge( RotationTransformer.Shape() );

		/* The second involute section begins with point P5 and ends with P6 */
		gp_Pnt P5 = Involute::getOuterEnd( ToothFaceSection2 );
		gp_Pnt P6 = Involute::getBaseEnd( ToothFaceSection2 );

		/* ========== TOP LAND SECTION ========== */
		/* P4 -----------------> Arc -----------------> P5 */
		/* Create Top land section */
		/* Top land section is defined as an arc between points P4 and P5 of the outside circle radius */
		/* ... calculate one more point laying on the outside circle to have 3 points defining the arc */
		gp_Pnt TopLandPoint = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::OUTSIDE_DIAMETER, Equations<GEAR_TYPE>>() ), ( (* Parameters->get<GearParameterTagCollection::TOOTH_BASE_ANGLE, Equations<GEAR_TYPE>>() ) / 2.0 ) );

		/* ... create top land section */
		TopoDS_Edge TopLandSection = BRepBuilderAPI_MakeEdge( GC_MakeArcOfCircle( P4 , TopLandPoint, P5 ).Value() );

		/* ========== TOOTH FLANK SECTION 2 ========== */
		/* P6 -----------------> Straight line -----------------> P7 */
		/* Point P7 lays on base circle at dedendum angle */
		gp_Pnt P7 = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::ROOT_DIAMETER, Equations<GEAR_TYPE>>() ), (* Parameters->get<GearParameterTagCollection::TOOTH_BASE_ANGLE, Equations<GEAR_TYPE>>() ) );

		TopoDS_Edge ToothFlankSection2 = BRepBuilderAPI_MakeEdge( P6, P7 );

		/* ========== BOTTOM LAND SECTION 2 ========== */
		/* P7 -----------------> Arc -----------------> P8 */
		gp_Pnt P8 = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::ROOT_DIAMETER, Equations<GEAR_TYPE>>() ), ProfileEndAngle );

		/* Calculate one more point on root circle to define the arc */
		/* Calculate one bottom land point to define the arc of root circle diameter */
		gp_Pnt BottomLandPoint2 = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::ROOT_DIAMETER, Equations<GEAR_TYPE>>() ), ( ( ProfileEndAngle + (* Parameters->get<GearParameterTagCollection::TOOTH_BASE_ANGLE, Equations<GEAR_TYPE>>() ) ) / 2.0 ) );

		/* ... create bottom land section */
		TopoDS_Edge BottomLandSection2 = BRepBuilderAPI_MakeEdge( GC_MakeArcOfCircle( P7 , BottomLandPoint2, P8 ).Value() );

		/* ========== BOTTOM LAND FILLET SECTION 2 ========== */
		/* Create fillet section edge */
		TopoDS_Edge BottomLandFilletSection2;

		ChFi2d_FilletAPI BottomLandFillet2( ToothFlankSection2, BottomLandSection2, ToothProfilePlane );

		/* Perform the fillet construction and check for the result */
		if( BottomLandFillet2.Perform( Parameters->get<GearParameterTagCollection::FILLET_RADIUS, Equations<GEAR_TYPE>>()->value() ) != true)
		{
			/* No fillet solution found */
			BOOST_THROW_EXCEPTION( Component::Exception::Design::ModelConstructionFailed() << Core::Exception::Message( "Fillet construction failed." ) );
		}

		/* The fillet is constructed, both original edges are modified */
		BottomLandFilletSection2 = BottomLandFillet2.Result( P7, ToothFlankSection2, BottomLandSection2 );

	#if 0
		/* ========== TOOTH PROFILE INTERFACE EDGES ========== */
		/* Calculate the two points laying on the rim circle */
		gp_Pnt P9 = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::RIM_DIAMETER, Equations<GEAR_TYPE>>() ), ProfileEndAngle );
		gp_Pnt P10 = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::RIM_DIAMETER, Equations<GEAR_TYPE>>() ), ProfileStartAngle );

		/* P8 -----------------> Straight line -----------------> P9 */
		TopoDS_Edge ToothInterfaceEdge1 = BRepBuilderAPI_MakeEdge( P8, P9 );
		/* P10 -----------------> Straight line -----------------> P1 */
		TopoDS_Edge ToothInterfaceEdge2 = BRepBuilderAPI_MakeEdge( P10, P1 );

		/* ========== RIM SECTION ========== */
		/* P8 -----------------> Arc -----------------> P9 */
		/* Calculate one more point laying on the rim circle */
		gp_Pnt RimCirclePoint = calcPointOnCircle( (* Parameters->get<GearParameterTagCollection::RIM_DIAMETER, Equations<GEAR_TYPE>>() ), ( (* Parameters->get<GearParameterTagCollection::TOOTH_BASE_ANGLE, Equations<GEAR_TYPE>>() ) / 2.0 ) );

		/* Create rim section */
		TopoDS_Edge RimSection = BRepBuilderAPI_MakeEdge( GC_MakeArcOfCircle( P9 , RimCirclePoint, P10 ).Value() );
	#endif

		/* Make tooth profile wire using the profile sections calculated before */
		ToothProfileWireMaker.Add( BottomLandSection1 );
		if( Parameters->get<GearParameterTagCollection::FILLET_RADIUS, Equations<GEAR_TYPE>>()->value() != 0 )
		{
			ToothProfileWireMaker.Add( BottomLandFilletSection1 );
		}
		ToothProfileWireMaker.Add( ToothFlankSection1 );
		ToothProfileWireMaker.Add( ToothFaceSection1 );
		ToothProfileWireMaker.Add( TopLandSection );
		ToothProfileWireMaker.Add( ToothFaceSection2 );
		ToothProfileWireMaker.Add( ToothFlankSection2 );
		if( Parameters->get<GearParameterTagCollection::FILLET_RADIUS, Equations<GEAR_TYPE>>()->value() != 0 )
		{
			ToothProfileWireMaker.Add( BottomLandFilletSection2 );
		}
		ToothProfileWireMaker.Add( BottomLandSection2 );
	#if 0
		ToothProfileWireMaker.Add( ToothInterfaceEdge1 );
		ToothProfileWireMaker.Add( RimSection );
		ToothProfileWireMaker.Add( ToothInterfaceEdge2 );
	#endif



		/* If the tooth profile wire is successfully constructed, store it. Otherwise throw tooth profile construction failed exception */
		if( ToothProfileWireMaker.IsDone() == true )
		{
			return( std::make_unique<TopoDS_Wire>( ToothProfileWireMaker.Wire() ) );
		}
		else
		{
			/* TODO: Add error code ( ToothProfileWireMaker.Error() ) */
			BOOST_THROW_EXCEPTION( Component::Exception::Design::ModelConstructionFailed() << Core::Exception::Message( "Tooth profile wire construction failed." ) );
		}
	}

	template<typename GEAR_TYPE>
	GEAR_EXPORT std::unique_ptr<TopoDS_Wire> ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Chain>::operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const
	{
		std::cout << "Creating CHAIN tooth profile." << std::endl;

		TopoDS_Wire tToothProfile;

		return( std::make_unique<TopoDS_Wire>( tToothProfile ) );
	}

	template<typename GEAR_TYPE>
	GEAR_EXPORT std::unique_ptr<TopoDS_Wire> ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Belt>::operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const
	{
		std::cout << "Creating BELT tooth profile." << std::endl;

		TopoDS_Wire tToothProfile;

		return( std::make_unique<TopoDS_Wire>( tToothProfile ) );
	}
}
