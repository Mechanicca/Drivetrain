/*
 * TeethCuttingTool.h
 *
 *  Created on: 12. 5. 2017
 *      Author: martin
 */

#ifndef PLUGIN_GEARS_DESIGN_GEAR_CONSTRUCTION_TEETHCUTTER_H_
#define PLUGIN_GEARS_DESIGN_GEAR_CONSTRUCTION_TEETHCUTTER_H_

/* Standard library inclusions */
#include <memory>

/* Project specific inclusions */
#include "Component/IComponentModel.h"
#include "Component/ComponentModelModifier.h"

#include "Parameter/Parameter.h"
#include "Parameter/ParameterContainer.h"

#include "Gear/GearTypes.h"

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
class TopoDS_Shape;

namespace Base
{
	class ParameterContainer;
}

namespace Design
{
	/** @brief Teeth cutter component modifier
	 *
	 *  Teeth cutter is a component modifier in [DECORATOR] design pattern.
	 *  Corresponds to Concrete decorator in http://www.oodesign.com/decorator-pattern.html
	 */
	template<typename GEAR_TYPE>
	class GEAR_EXPORT TeethCutter
		:	/* Derives ComponentModifier according to decorator pattern */
			public Component::ComponentModelModifier
	{
	public:
		TeethCutter( std::shared_ptr<Component::IComponentModel> ComponentModel );

		std::unique_ptr<TopoDS_Shape> constructModelModifier( const std::shared_ptr<Core::ParameterContainer> Parameters ) const override final;

		std::unique_ptr<TopoDS_Shape> applyModifier( const std::shared_ptr<TopoDS_Shape> ComponentShape, const std::shared_ptr<TopoDS_Shape> ModifierShape ) const override final;

	protected:

	private:

	};

	/* Instantiate all supported TeethCutters */
	template class GEAR_EXPORT TeethCutter<GearType::SpurRack>;
	template class GEAR_EXPORT TeethCutter<GearType::SpurGear>;
	template class GEAR_EXPORT TeethCutter<GearType::InternalSpurGear>;
	template class GEAR_EXPORT TeethCutter<GearType::HelicalRack>;
	template class GEAR_EXPORT TeethCutter<GearType::HelicalGear>;
	template class GEAR_EXPORT TeethCutter<GearType::InternalHelicalGear>;
	template class GEAR_EXPORT TeethCutter<GearType::Sprocket>;
	template class GEAR_EXPORT TeethCutter<GearType::Pulley>;
#if 0
	template class GEAR_EXPORT TeethCutter<GearType::StraightBevelGear>;
	template class GEAR_EXPORT TeethCutter<GearType::SpiralBevelGear>;
	template class GEAR_EXPORT TeethCutter<GearType::ZerolGear>;
#endif
}

#endif /* PLUGIN_GEARS_DESIGN_GEAR_CONSTRUCTION_TEETHCUTTER_H_ */
