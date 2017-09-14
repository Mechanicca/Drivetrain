/*
 * Equations.h
 *
 *  Created on: 5. 5. 2017
 *      Author: martin
 */

#ifndef PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_EQUATIONS_H_
#define PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_EQUATIONS_H_

/* Project specific inclusions */
#include "Equation/Equation.h"
#include "Component/Exception.h"

#include "GearTypes.h"
#include "GearParameterTagCollection.h"

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

namespace Design
{
	template<typename GEAR_TYPE> class Equations {};

	/**
	 * @brief Gear parameter Addendum equation
	 *
	 * Addendum is equal to module multiplied by a factor defined by used Standard Tooth System:
	 * h_a = m * factor
	 *
	 * Parameter: Addendum
	 * Designer:  Rim
	 * Usable:    All gear types (FIXME: Should also be applicable to racks)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::ADDENDUM, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::ADDENDUM::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) * (* Parameters->get<GearParameterTagCollection::ADDENDUM_FACTOR, Equations<GEAR_TYPE>>() ) );
		}
	};

	/**
	 * @brief Gear parameter Dedendum equation
	 *
	 * Addendum is equal to module multiplied by a factor defined by used Standard Tooth System:
	 * h_f = m * factor
	 *
	 * Parameter: Dedendum
	 * Designer:  Rim
	 * Usable:    All gear types (FIXME: Should also be applicable to racks)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::DEDENDUM, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::DEDENDUM::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) * (* Parameters->get<GearParameterTagCollection::DEDENDUM_FACTOR, Equations<GEAR_TYPE>>() ) );
		}
	};

	/**
	 * @brief Gear parameter Pressure angle
	 *
	 * Pressure angle is calculated by factor defined by used Standard Tooth System:
	 * alpha = PI / factor [rad]
	 *
	 * Parameter: Pressure angle
	 * Designer:  Rim
	 * Usable:    All gear types (TODO: Should also be applicable to racks??)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::PRESSURE_ANGLE, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::PRESSURE_ANGLE::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( ( boost::math::constants::pi<double>() / (* Parameters->get<GearParameterTagCollection::PRESSURE_ANGLE_FACTOR, Equations<GEAR_TYPE>>() ) ) * si::radians );
		}
	};

	/**
	 * @brief Gear parameter Tooth base circle angle
	 *
	 * Tooth base circle angle is calculated by the formula:
	 * phi_f = ( (pi * m) / d ) + 2( t - atan( t ) )
	 *
	 * where
	 * t = ( d / d_b ) - 1
	 *
	 * Parameter: Tooth base circle angle
	 * Designer:  Rim
	 * Usable:    All gear types
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::TOOTH_BASE_ANGLE, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::TOOTH_BASE_ANGLE::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			double t ( ( (* Parameters->get<GearParameterTagCollection::STANDARD_PITCH_DIAMETER, Equations<GEAR_TYPE>>() ) / (* Parameters->get<GearParameterTagCollection::BASE_DIAMETER, Equations<GEAR_TYPE>>() ) ) - 1.0 );

			return( ( ( ( boost::math::constants::pi<double>() * (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) ) / (* Parameters->get<GearParameterTagCollection::STANDARD_PITCH_DIAMETER, Equations<GEAR_TYPE>>() ) ) + 2 * ( t - std::atan( t ) ) ) * si::radians );
		}
	};

	/**
	 * @brief Gear parameter Standard pitch diameter equation
	 *
	 * Standard pitch diameter is calculated using the formula:
	 * d_p = m * z
	 *
	 * Parameter: Standard pitch diameter
	 * Designer:  Rim
	 * Usable:    All gear types
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::STANDARD_PITCH_DIAMETER, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::STANDARD_PITCH_DIAMETER::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) * (* Parameters->get<GearParameterTagCollection::NUM_OF_TEETH, Equations<GEAR_TYPE>>() ) );
		}
	};

	/**
	 * @brief Gear parameter Base diameter equation
	 *
	 * Base diameter is calculated using the formula:
	 * d_b = d * cos( alpha )
	 *
	 * Parameter: Base diameter
	 * Designer:  Rim
	 * Usable:    All gear types
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::BASE_DIAMETER, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::BASE_DIAMETER::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::STANDARD_PITCH_DIAMETER, Equations<GEAR_TYPE>>() ) * boost::units::cos( (* Parameters->get<GearParameterTagCollection::PRESSURE_ANGLE, Equations<GEAR_TYPE>>() ) ) );
		}
	};

	/**
	 * @brief Gear parameter Root diameter equation
	 *
	 * Root diameter is calculated using the formula:
	 * d_f = ( d - 2h_f )
	 *
	 * Parameter: Root diameter
	 * Designer:  Rim
	 * Usable:    All gear types
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::ROOT_DIAMETER, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::ROOT_DIAMETER::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::STANDARD_PITCH_DIAMETER, Equations<GEAR_TYPE>>() ) - ( 2.0 * (* Parameters->get<GearParameterTagCollection::DEDENDUM, Equations<GEAR_TYPE>>() ) ) );
		}
	};

	/**
	 * @brief Gear parameter Outside diameter equation
	 *
	 * Outside diameter is calculated using the formula:
	 * d_a = (z + 2) * m
	 *
	 * The equation is equivalent to:
	 * d_a = d + 2m
	 *
	 * Parameter: Outside diameter
	 * Designer:  Rim
	 * Usable:    All gear types
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::OUTSIDE_DIAMETER, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::OUTSIDE_DIAMETER::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::STANDARD_PITCH_DIAMETER, Equations<GEAR_TYPE>>() ) + ( 2.0 * (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) ) );
		}
	};

	/**
	 * @brief Gear parameter Working depth
	 *
	 * Working depth is calculated using the formula:
	 * h_w = 2 * m
	 *
	 * Parameter: Working depth
	 * Designer:  Rim
	 * Usable:    All gear types (FIXME: Should also be applicable to racks)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::WORKING_DEPTH, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::WORKING_DEPTH::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( 2.0 * (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) );
		}
	};

	/**
	 * @brief Gear parameter Whole depth equation
	 *
	 * Working depth is calculated as sum of addendum and dedendum using the formula:
	 * h = h_a + h_f
	 *
	 * Parameter: Whole depth
	 * Designer:  Rim
	 * Usable:    All gear types (FIXME: Should also be applicable to racks)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::WHOLE_DEPTH, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::WHOLE_DEPTH::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::ADDENDUM, Equations<GEAR_TYPE>>() ) + (* Parameters->get<GearParameterTagCollection::DEDENDUM, Equations<GEAR_TYPE>>() ) );
		}
	};

	/**
	 * @brief Gear parameter Clearance equation
	 *
	 * Clearance is equal to WholeDepth - WorkingDepth
	 * c = h - h_f
	 *
	 * Parameter: Clearance
	 * Designer:  Rim
	 * Usable:    All gear types (FIXME: Should also be applicable to racks)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::CLEARANCE, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::CLEARANCE::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::WHOLE_DEPTH, Equations<GEAR_TYPE>>() ) - (* Parameters->get<GearParameterTagCollection::WORKING_DEPTH, Equations<GEAR_TYPE>>() ) );
		}
	};

	/**
	 * @brief Gear parameter Angular tooth width equation
	 *
	 * Clearance is equal to WholeDepth - WorkingDepth
	 * psi = 2pi / z [rad]
	 *
	 * Parameter: Angular tooth width
	 * Designer:  Rim
	 * Usable:    All gear types (FIXME: Should also be applicable to racks)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::ANGULAR_TOOTH_WIDTH, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::ANGULAR_TOOTH_WIDTH::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( ( ( 2.0 * boost::math::constants::pi<double>() ) / (* Parameters->get<GearParameterTagCollection::NUM_OF_TEETH, Equations<GEAR_TYPE>>() ) ) * si::radians );
		}
	};

	/**
	 * @brief Gear parameter Fillet radius equation
	 *
	 * Fillet radius is calculated by a multiplier factor using the formula:
	 * r_f = m * x_rf
	 *
	 * Constraint: Fillet radius must not be bigger than the difference between the base circle radius and root circle radius. If so,
	 *             the fillet construction fails.
	 *
	 * Parameter: Fillet radius
	 * Designer:  Rim
	 * Usable:    All gear types (FIXME: Should also be applicable to racks)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::FILLET_RADIUS, UsableFor<GEAR_TYPE, GearProperties::GearType::Gear>>
	{
		GEAR_EXPORT GearParameterTagCollection::FILLET_RADIUS::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			/* Create temporary fillet quantities */
			GearParameterTagCollection::FILLET_RADIUS::TParameter::TQuantity tFilletRadius, tMaxFilletRadius;

			/* Calculate "regular" fillet radius as specified */
			tFilletRadius = ( (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) * (* Parameters->get<GearParameterTagCollection::FILLET_RADIUS_FACTOR, Equations<GEAR_TYPE>>() ) );
			/* Calculate maximum possible fillet radius defined by Base and Root circle */
			tMaxFilletRadius = ( ( (* Parameters->get<GearParameterTagCollection::BASE_DIAMETER, Equations<GEAR_TYPE>>() ) - (* Parameters->get<GearParameterTagCollection::ROOT_DIAMETER, Equations<GEAR_TYPE>>() ) ) / 2.0 );

			/* Decide which fillet radius to use and return apropriate option */
			if( tFilletRadius < tMaxFilletRadius ) return( tFilletRadius ); else return( tMaxFilletRadius );
		}
	};

	/**
	 * @brief Gear parameter Rim diameter equation
	 *
	 * Rim internal diameter is equal to outside diameter - factor * module:
	 * d_r = d_a - ( x_dr * m )
	 *
	 * Parameter: Rim diameter
	 * Designer:  Rim
	 * Usable:    External rim types
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::RIM_DIAMETER, UsableFor<GEAR_TYPE, GearProperties::RimType::External>>
	{
		GEAR_EXPORT GearParameterTagCollection::RIM_DIAMETER::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( (* Parameters->get<GearParameterTagCollection::OUTSIDE_DIAMETER, Equations<GEAR_TYPE>>() ) - ( (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) * (* Parameters->get<GearParameterTagCollection::RIM_DIAMETER_FACTOR, Equations<GEAR_TYPE>>() ) ) );
		}
	};

	/**
	 * @brief Gear parameter Rim diameter equation
	 *
	 * In order to calculate rim diameter at least one of the two parameters RIM_THICKNESS or INTERNAL_GEAR_RIM_DIAMETER must be provided in specification.
	 * When INTERNAL_GEAR_RIM_DIAMETER is provided, it is checked to be big enough the rim has minimum thickness as defined in design rules DB. If smaller,
	 * the rim diameter is calculated as sum of OUTSIDE_DIAMETER and minimum rim thickness.
	 *
	 * If RIM_THICKNESS is provided in specification the rim diameter is calculated using the formula:
	 * d_r = d_a + 2t_r
	 *
	 * Parameter: Rim diameter
	 * Designer:  Rim
	 * Usable:    Internal rim types
	 *
	 * @throws <Exception::SpecificationIncomplete> {None of the required parameters (INTERNAL_GEAR_RIM_DIAMETER or RIM_THICKNESS) was provided in specification}
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::RIM_DIAMETER, UsableFor<GEAR_TYPE, GearProperties::RimType::Internal>>
	{
		GEAR_EXPORT GearParameterTagCollection::RIM_DIAMETER::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			/* Temporary rim diameter quantity to return */
			GearParameterTagCollection::RIM_DIAMETER::TParameter::TQuantity tRimDiameterQuantity;

			/* Read rim thickness from the design rules */
			GearParameterTagCollection::RIM_THICKNESS RimThicknessParamID;
			GearParameterTagCollection::RIM_THICKNESS::TParameter tRimThickness( RimThicknessParamID );

			/* Get the minimum rim thickness from design rules DB */
			GearParameterTagCollection::RIM_THICKNESS::TParameter::TQuantity tMinimumRimThicknessQuantity = tRimThickness.getLimits().first;

			/* If internal gear rim diameter is specified */
			if( Parameters->isAvailable<GearParameterTagCollection::INTERNAL_GEAR_RIM_DIAMETER>() )
			{
				/* Specified internal rim diameter must be bigger or equal to gear's outside diameter */
				if( (* Parameters->get<GearParameterTagCollection::INTERNAL_GEAR_RIM_DIAMETER, Equations<GEAR_TYPE>>() ) >= ( (* Parameters->get<GearParameterTagCollection::OUTSIDE_DIAMETER, Equations<GEAR_TYPE>>() ) + tMinimumRimThicknessQuantity ) )
					/* If so, use the specified internal rim diameter */
					tRimDiameterQuantity = (* Parameters->get<GearParameterTagCollection::INTERNAL_GEAR_RIM_DIAMETER, Equations<GEAR_TYPE>>() );
				else
					/* Use the minimum constructible rim thickness */
					tRimDiameterQuantity = ( (* Parameters->get<GearParameterTagCollection::OUTSIDE_DIAMETER, Equations<GEAR_TYPE>>() ) + tMinimumRimThicknessQuantity );

					/* TODO: Place a warning that INTERNAL_GEAR_RIM_DIAMETER is too small and has been adjusted to the minimum constructible value */
			}
			/* If rim thickness is specified */
			else if( Parameters->isAvailable<GearParameterTagCollection::RIM_THICKNESS>() )
			{
				/* NOTE: Rim thickness is in range of it's limits as secured by the parameter itself. There is no need to check whether the quantity is above the minimum limit */
				tRimDiameterQuantity = (* Parameters->get<GearParameterTagCollection::OUTSIDE_DIAMETER, Equations<GEAR_TYPE>>() ) + ( 2.0 * (* Parameters->get<GearParameterTagCollection::RIM_THICKNESS, Equations<GEAR_TYPE>>() ) );
			}
			/* None of the required specification parameters are supplied so there is no way to construct the gear --> throw an exception */
			else
			{
				/* Throw specification incomplete exception to inform which parameters are requested */
				BOOST_THROW_EXCEPTION( Component::Exception::Design::SpecificationIncomplete() << Core::Exception::Message( "Rim diameter or rim thickness must be specified." ) );
			}

			/* Return calculated rim diameter quantity */
			return( tRimDiameterQuantity );
		}
	};

	/**
	 * @brief Gear parameter Circular tooth thickness
	 *
	 * Circular tooth thickness is calculated using the formula:
	 * s = ( PI / 2 ) * m
	 *
	 * Parameter: Circular tooth thickness
	 * Designer:  Rim
	 * Usable:    External rim types (FIXME: may be valid also for internal rim types / racks?)
	 */
	template<typename GEAR_TYPE>
	struct GEAR_EXPORT Equation<Equations<GEAR_TYPE>, GearParameterTagCollection::CIRCULAR_TOOTH_THICKNESS, UsableFor<GEAR_TYPE, GearProperties::RimType::External>>
	{
		GEAR_EXPORT GearParameterTagCollection::CIRCULAR_TOOTH_THICKNESS::TParameter::TQuantity operator() ( const std::shared_ptr<Core::ParameterContainer> Parameters ) const
		{
			return( ( boost::math::constants::pi<double>() / 2.0 ) / (* Parameters->get<GearParameterTagCollection::MODULE, Equations<GEAR_TYPE>>() ) );
		}
	};
}

#endif /* PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_EQUATIONS_H_ */
