/*
 * TeethCuttingTool.cpp
 *
 *  Created on: 12. 5. 2017
 *      Author: martin
 */

/* Standard library inclusions */
#include <thread>
#include <chrono>

/* OpenCascade inclusions */
#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx> /* TODO: Remove, temporary */
#include <BRepAlgoAPI_Cut.hxx>

/* Project specific inclusions */
#include "Parameter/ParameterContainer.h"

#include "Design/ToothProfiler.h"

#include "Design/TeethCutter.h"

namespace Design
{
	template<typename GEAR_TYPE>
	TeethCutter<GEAR_TYPE>::TeethCutter( std::shared_ptr<Component::IComponentModel> ComponentModel )
		:	/* Construct base component modifier first */
			Component::ComponentModelModifier( ComponentModel )
	{}

	template<typename GEAR_TYPE>
	std::unique_ptr<TopoDS_Shape> TeethCutter<GEAR_TYPE>::constructModelModifier( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
	{
		std::cout << "Constructing TEETH CUTTER model modifier." << std::endl;

		std::cout << "Getting tooth profile..." << std::endl;

		std::unique_ptr<TopoDS_Wire> tProfile = ToothProfiler<GEAR_TYPE>()( Parameters );

		BRepPrimAPI_MakeCylinder tCylinderMaker( 0.25, 1.0 );

		std::unique_ptr<TopoDS_Shape> tShape = std::make_unique<TopoDS_Shape>( tCylinderMaker.Shape() );

		/* TODO: Remove --> Long task simulation */
		std::this_thread::sleep_for( std::chrono::milliseconds(2000) );

		std::cout << "TEETH CUTTER model modifier done." << std::endl;

		return( std::move( tShape ) );
	}

	template<typename GEAR_TYPE>
	std::unique_ptr<TopoDS_Shape> TeethCutter<GEAR_TYPE>::applyModifier( const std::shared_ptr<TopoDS_Shape> ComponentShape, const std::shared_ptr<TopoDS_Shape> ModifierShape ) const
	{
		std::cout << "Applying TEETH CUTTER component model modifier." << std::endl;

		std::unique_ptr<TopoDS_Shape> tShape = std::make_unique<TopoDS_Shape>( BRepAlgoAPI_Cut( (* ComponentShape), (* ModifierShape) ).Shape() );

		/* TODO: Remove --> Long task simulation */
		std::this_thread::sleep_for( std::chrono::milliseconds(2500) );

		std::cout << "TEETH CUTTER component model modifier applied." << std::endl;

		return( std::move( tShape ) );
	}
}
