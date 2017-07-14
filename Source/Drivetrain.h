/*
 * GearsPlugin.h
 *
 *  Created on: 21. 4. 2017
 *      Author: martin
 */

#ifndef DRIVETRAIN_DRIVETRAIN_H_
#define DRIVETRAIN_DRIVETRAIN_H_

/* Standard library inclusions */
#include <memory>
#include <list>

/* Boost inclusions */
#include <boost/dll/alias.hpp>

/* Project specific inclusions */
#include "Component/IComponent.h"
#include "Component/IComponentDesigner.h"
#include "Component/IComponentPluginAPI.h"

namespace Drivetrain
{
	class DrivetrainPlugin
		:	/* Implements component plugin interface */
			public Component::Plugin::API::IComponentPluginAPI
	{
	public:
		DrivetrainPlugin( void );

		const std::string & getPluginName( void ) const override final;

		const std::string & getPluginVersion( void ) const override final;

		const Component::Plugin::API::IComponentPluginAPI::TIComponentDesignerList getComponentDesigners( void ) const override final;

		static std::shared_ptr<Component::Plugin::API::IComponentPluginAPI> Load( void )
		{
			return( std::make_shared<DrivetrainPlugin>() );
		}

	protected:

	private:
		std::string mPluginName;

		std::string mPluginVersion;

	};

	BOOST_DLL_ALIAS( Drivetrain::DrivetrainPlugin::Load, LoadPlugin )
}

#endif /* DRIVETRAIN_DRIVETRAIN_H_ */
