/*
 * GearBlank.h
 *
 *  Created on: 15. 5. 2017
 *      Author: martin
 */

#ifndef PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_GEARBLANK_H_
#define PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_GEARBLANK_H_

/* Standard library inclusions */
#include <memory>
#include <future>

/* Project specific inclusions */
#include "Component/ComponentModel.h"

#include "Gear/GearTypes.h"

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

/* Forward declarations */
class TopoDS_Shape;

namespace Base
{
	class ParameterContainer;
}

namespace Design
{
	template<typename GEAR_TYPE>
	class GearBlank
		:	public Component::ComponentModel
	{
	public:
		GearBlank( void );

	protected:

	private:
		std::unique_ptr<TopoDS_Shape> constructComponentModel( const std::shared_ptr<Core::ParameterContainer> Parameters ) const override final;
	};

	/* Instantiate all supported GearBlank specializations */
	template class GEAR_NO_EXPORT GearBlank<GearType::SpurRack>;
	template class GEAR_NO_EXPORT GearBlank<GearType::SpurGear>;
	template class GEAR_NO_EXPORT GearBlank<GearType::InternalSpurGear>;
	template class GEAR_NO_EXPORT GearBlank<GearType::HelicalRack>;
	template class GEAR_NO_EXPORT GearBlank<GearType::HelicalGear>;
	template class GEAR_NO_EXPORT GearBlank<GearType::InternalHelicalGear>;
	template class GEAR_NO_EXPORT GearBlank<GearType::Sprocket>;
	template class GEAR_NO_EXPORT GearBlank<GearType::Pulley>;
#if 0
	template class GEAR_NO_EXPORT GearBlank<GearType::StraightBevelGear>;
	template class GEAR_NO_EXPORT GearBlank<GearType::SpiralBevelGear>;
	template class GEAR_NO_EXPORT GearBlank<GearType::ZerolGear>;
#endif
}

#endif /* PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_GEARBLANK_H_ */
