/*
 * Gear.cpp
 *
 *  Created on: 27. 4. 2017
 *      Author: martin
 */

/* Standard library inclusions */
#include <chrono>

/* OpenCascade inclusions */
#include <TopoDS_Shape.hxx>

/* Project specific inclusions */
#include "Gear/Gear.h"

#include "Component/IComponentModel.h"
#include "Component/ComponentModel.h"

#include "Design/Exception.h"
#if false
#include "Design/TeethCutter.h"
#include "Design/GearBlank.h"
#endif

#define DEBUG_CONSOLE_OUTPUT	false

namespace Component
{
	template<typename GEAR_TYPE>
	Gear<GEAR_TYPE>::Gear( const std::shared_ptr<Core::ParameterContainer> Specification )
		:	/* Initialize component base first */
			Component<Gear<GEAR_TYPE>>( Specification )
	{}
}

#undef DEBUG_CONSOLE_OUTPUT
