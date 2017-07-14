/*
 * Drivetrain.cpp
 *
 *  Created on: 21. 4. 2017
 *      Author: martin
 */

/* All components root headers */
#include "Gear/Gear.h"

/* [GENERATED] */
#include "Version.h"

#ifndef VERSION_COMPLETE_STRING
#define VERSION_COMPLETE_STRING "Unknown"
#endif

/* Project specific inclusions */
#include "Component/ComponentDesigner.h"
#include "Drivetrain.h"

using namespace Component::Plugin::API;

namespace Drivetrain
{
	DrivetrainPlugin::DrivetrainPlugin( void )
		:	/* Initialize plugin name */
			mPluginName( "Drivetrain" ),
			/* Plugin version */
			mPluginVersion( VERSION_COMPLETE_STRING )
	{
	}

	const IComponentPluginAPI::TIComponentDesignerList DrivetrainPlugin::getComponentDesigners( void ) const
	{
		/* Construct sample list of fake component designers */
		IComponentPluginAPI::TIComponentDesignerList tComponentDesignerList;

		/* List all component designers to produce components of all supported types */
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::SpurRack>>>( "SpurRack", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::SpurGear>>>( "SpurGear", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::InternalSpurGear>>>( "InternalSpurGear", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::HelicalRack>>>( "HelicalRack", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::HelicalGear>>>( "HelicalGear", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::InternalHelicalGear>>>( "InternalHelicalGear", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::Sprocket>>>( "Sprocket", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::Pulley>>>( "Pulley", "Gears" ) );
	#if false
		/* Not yet supported */
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::StraightBevelGear>>>( "StraightBevelGear", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::SpiralBevelGear>>>( "SpiralBevelGear", "Gears" ) );
		tComponentDesignerList.push_back( std::make_shared<Component::ComponentDesigner<Component::Gear<GearType::ZerolGear>>>( "ZerolGear", "Gears" ) );
	#endif

		return( tComponentDesignerList );
	}

	const std::string & DrivetrainPlugin::getPluginName( void ) const
	{
		/* TODO: Make this generated as well */
		return( mPluginName );
	}

	const std::string & DrivetrainPlugin::getPluginVersion( void ) const
	{
		return( mPluginVersion );
	}
}
