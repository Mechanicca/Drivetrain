/*
 * Gear_Types.h
 *
 *  Created on: 12.11.2015
 *      Author: martin
 */

#ifndef SOURCE_COMPONENTS_GEAR_GEAR_TYPES_H_
#define SOURCE_COMPONENTS_GEAR_GEAR_TYPES_H_

/* Boost inclusions */
/* Standard library inclusions */
#include <type_traits>

/* Boost inclusions */

namespace GearProperties
{
	namespace GearType
	{
		class Gear {};
		class Rack {};
	}

	/* Rim type TAGs */
	namespace RimType
	{
		class Radial {};
		class Axial {};

		class External : Axial {};
		class Internal : Axial {};
		class Bevel    : Radial {};
	}

	/* Tooth profile TAGs */
	namespace ToothProfile
	{
		class Involute {};
		class Straight {};
		class Chain {};
		class Belt {};
	}

	/* Tooth shape TAGs */
	namespace ToothShape
	{
		class Spur {};
		class Helical {};
	}
}

namespace GearType
{
	using namespace GearProperties;

	class SpurRack 				:	GearProperties::GearType::Rack, GearProperties::ToothProfile::Straight, GearProperties::ToothShape::Spur {};
	class HelicalRack 			:	GearProperties::GearType::Rack, GearProperties::ToothProfile::Straight, GearProperties::ToothShape::Helical {};
	class SpurGear 				:	GearProperties::GearType::Gear, GearProperties::RimType::External, GearProperties::ToothProfile::Involute, GearProperties::ToothShape::Spur {};
	class InternalSpurGear		:	GearProperties::GearType::Gear, GearProperties::RimType::Internal, GearProperties::ToothProfile::Involute, GearProperties::ToothShape::Spur {};
	class HelicalGear			:	GearProperties::GearType::Gear, GearProperties::RimType::External, GearProperties::ToothProfile::Involute, GearProperties::ToothShape::Helical {};
	class InternalHelicalGear	:	GearProperties::GearType::Gear, GearProperties::RimType::Internal, GearProperties::ToothProfile::Involute, GearProperties::ToothShape::Helical {};
	class Sprocket				:	GearProperties::GearType::Gear, GearProperties::RimType::External, GearProperties::ToothProfile::Chain, GearProperties::ToothShape::Spur {};
	class Pulley				:	GearProperties::GearType::Gear, GearProperties::RimType::External, GearProperties::ToothProfile::Belt, GearProperties::ToothShape::Spur {};
#if 0
	class StraightBevelGear		:	GearProperties::GearType::Gear, GearProperties::RimType::Bevel, GearProperties::ToothProfile::Straight, GearProperties::ToothShape::Spur {};
	class SpiralBevelGear		:	GearProperties::GearType::Gear, GearProperties::RimType::Bevel, GearProperties::ToothProfile::Straight, GearProperties::ToothShape::Helical {};
	class ZerolGear {};
#endif
}

template<typename TAG, typename... OTHER_BASE_TAGS>
struct tag_cast
{
    using type = TAG;
};

template<typename TAG, typename BASE_TAG, typename ... OTHER_BASE_TAGS>
struct tag_cast<TAG, BASE_TAG, OTHER_BASE_TAGS...>
{
    using type = typename std::conditional<std::is_base_of<BASE_TAG, TAG>::value, BASE_TAG, typename tag_cast<TAG, OTHER_BASE_TAGS ...>::type>::type;
};

#endif /* SOURCE_COMPONENTS_GEAR_GEAR_TYPES_H_ */
