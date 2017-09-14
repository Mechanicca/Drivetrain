/*
 * Gear.h
 *
 *  Created on: 27. 4. 2017
 *      Author: martin
 */

#ifndef DRIVETRAIN_GEAR_GEAR_H_
#define DRIVETRAIN_GEAR_GEAR_H_

/* Standard library inclusions */
#include <memory>

/* Project specific inclusions */
#include "Parameter/ParameterContainer.h"
#include "Component/Component.h"

#include "Design/TeethCutter.h"
#include "Design/GearBlank.h"

#include "GearTypes.h"

/* [GENERATED] */
#include "Gear/GearParameterTagCollection.h"

/* Shared library support */
#include "DrivetrainExport.h"
/* As DrivetrainExport.h header is generated during build, the required DRIVETRAIN_EXPORT
 * definition might not exist due to missing header file. In order to prevent
 * syntax errors cause by undefined DRIVETRAIN_EXPORT, define temporary blank one */
/* [GENERATED] */
#ifndef DRIVETRAIN_EXPORT
	#define DRIVETRAIN_EXPORT
	#define DRIVETRAIN_NO_EXPORT
#endif

	class TopoDS_Shape;

/* Plugin's namespace */
namespace Component
{
	template<typename GEAR_TYPE> class Gear;

	/* ComponentTraits specialization for every Gear type */
	template<typename GEAR_TYPE>
	struct ComponentTraits<Gear<GEAR_TYPE>>
	{
		using TComponentModelConstructor = ComponentModelConstructor
			<
				Design::GearBlank<GEAR_TYPE>,
				Design::TeethCutter<GEAR_TYPE>
			>;
	};

	/* Forward declarations */
	class IComponentModel;

	template<typename GEAR_TYPE>
	class Gear
		:	/* Gear is a component which implements IComponent interface */
			public Component<Gear<GEAR_TYPE>>
	{
	public:

		Gear( const std::shared_ptr<Core::ParameterContainer> Specification );

	protected:

	private:

	};

	/* Instantiate all supported Gear specializations */
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::SpurRack>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::SpurGear>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::InternalSpurGear>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::HelicalRack>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::HelicalGear>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::InternalHelicalGear>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::Sprocket>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::Pulley>;
#if 0
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::StraightBevelGear>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::SpiralBevelGear>;
	template class DRIVETRAIN_NO_EXPORT Gear<GearType::ZerolGear>;
#endif
}

#endif /* DRIVETRAIN_GEAR_GEAR_H_ */
