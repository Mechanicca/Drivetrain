/*
 * ToothProfile.h
 *
 *  Created on: 4. 5. 2017
 *      Author: martin
 */

#ifndef PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_TOOTHPROFILER_H_
#define PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_TOOTHPROFILER_H_

/* Standard library inclusions */
#include <memory>

/* Project specific inclusions */
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

/* Parameter tags collection header is automatically generated
 * dependent on DesignRules.db. Once the database is updated, the header is
 * regenerated during the build. */
/* [GENERATED] */
#include "Gear/GearParameterTagCollection.h"

/* Forward declarations */
class TopoDS_Wire;

namespace Base
{
	class ParameterContainer;
}

namespace Design
{
	template<typename GEAR_TYPE>
	class ToothProfiler
	{
	public:
		std::unique_ptr<TopoDS_Wire> operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const;

	private:
		/* Dispatch the tag */
		using ToothProfileTag = typename tag_cast<GEAR_TYPE, GearProperties::ToothProfile::Straight, GearProperties::ToothProfile::Involute, GearProperties::ToothProfile::Chain, GearProperties::ToothProfile::Belt>::type;
	};

	/**
	 * @brief Tooth profile helper class
	 *
	 * Owns static method which constructs the tooth PROFILE of requested type
	 */
	template<typename GEAR_TYPE, typename TAG>
	struct GEAR_EXPORT ToothProfile;

	template<typename GEAR_TYPE>
	struct GEAR_EXPORT ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Straight>
	{
		GEAR_EXPORT std::unique_ptr<TopoDS_Wire> operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const;
	};

	template<typename GEAR_TYPE>
	struct GEAR_EXPORT ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Involute>
	{
		GEAR_EXPORT std::unique_ptr<TopoDS_Wire> operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const;
	};

	template<typename GEAR_TYPE>
	struct GEAR_EXPORT ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Chain>
	{
		GEAR_EXPORT std::unique_ptr<TopoDS_Wire> operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const;
	};

	template<typename GEAR_TYPE>
	struct GEAR_EXPORT ToothProfile<GEAR_TYPE, GearProperties::ToothProfile::Belt>
	{
		GEAR_EXPORT std::unique_ptr<TopoDS_Wire> operator() ( std::shared_ptr<Core::ParameterContainer> Parameters ) const;
	};

	/* Instantiate all supported ToothProfilers */
	template class GEAR_EXPORT ToothProfiler<GearType::SpurRack>;
	template class GEAR_EXPORT ToothProfiler<GearType::SpurGear>;
	template class GEAR_EXPORT ToothProfiler<GearType::InternalSpurGear>;
	template class GEAR_EXPORT ToothProfiler<GearType::HelicalRack>;
	template class GEAR_EXPORT ToothProfiler<GearType::HelicalGear>;
	template class GEAR_EXPORT ToothProfiler<GearType::InternalHelicalGear>;
	template class GEAR_EXPORT ToothProfiler<GearType::Sprocket>;
	template class GEAR_EXPORT ToothProfiler<GearType::Pulley>;
#if 0
	template class GEAR_EXPORT ToothProfiler<GearType::StraightBevelGear>;
	template class GEAR_EXPORT ToothProfiler<GearType::SpiralBevelGear>;
	template class GEAR_EXPORT ToothProfiler<GearType::ZerolGear>;
#endif
}

#endif /* PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_TOOTHPROFILER_H_ */
