/*
 * Exception.h
 *
 *  Created on: 4. 5. 2017
 *      Author: martin
 */

#ifndef PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_EXCEPTION_H_
#define PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_EXCEPTION_H_

/* Project specific inclusions */
#include "Exception/Exception.h"

/* Shared library support */
#include "Gear/GearExport.h"
/* As Component_Export.h header is generated during build, the required GEAR_EXPORT
 * definition might not exist due to missing header file. In order to prevent
 * syntax errors cause by undefined GEAR_EXPORT, define temporary blank one */
/* [GENERATED] */
#ifndef GEAR_EXPORT
	#define GEAR_EXPORT
	#define GEAR_NO_EXPORT
#endif

namespace Component
{
	namespace Exception
	{
		namespace Design
		{
			struct GEAR_EXPORT ModelConstructionFailed : virtual Core::Exception::Generic {};
			struct GEAR_EXPORT SpecificationIncomplete : virtual Core::Exception::Generic {};
		}
	}
}

#endif /* PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_EXCEPTION_H_ */
