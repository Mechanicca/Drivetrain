/*
 * GearBlank.cpp
 *
 *  Created on: 15. 5. 2017
 *      Author: martin
 */

/* OpenCascade inclusions */
#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx> /* TODO: Remove, temporary */

/* Project specific inclusions */
#include "GearBlank.h"

#include "Parameter/ParameterContainer.h"
#include "Gear/GearParameterTagCollection.h"

namespace Design
{
	template<typename GEAR_TYPE>
	GearBlank<GEAR_TYPE>::GearBlank( void )
	{
	}

	template<typename GEAR_TYPE>
	std::unique_ptr<TopoDS_Shape> GearBlank<GEAR_TYPE>::constructComponentModel( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
	{
		std::cout << "Constructing GEAR BLANK model." << std::endl;

		BRepPrimAPI_MakeBox tBoxMaker( 1.0, 1.0, 1.0 );

		std::unique_ptr<TopoDS_Shape> tShape = std::make_unique<TopoDS_Shape>( tBoxMaker.Shape() );

		/* TODO: Remove --> Long task simulation */
		std::this_thread::sleep_for( std::chrono::milliseconds(3000) );

		std::cout << "GEAR BLANK model done." << std::endl;

		return( std::move( tShape ) );
	}
}
