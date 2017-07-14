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
#include "Design/TeethCutter.h"
#include "Design/GearBlank.h"

#define DEBUG_CONSOLE_OUTPUT	true

namespace Component
{
	template<typename GEAR_TYPE>
	Gear<GEAR_TYPE>::Gear( const std::shared_ptr<Core::ParameterContainer> Specification )
		:	/* Initialize component base first */
			Component<Gear<GEAR_TYPE>>( Specification )
	{}

	template<typename GEAR_TYPE>
	void Gear<GEAR_TYPE>::update( void )
	{
		/* Create temporary component model and all it's modifiers */
		std::shared_ptr<IComponentModel> tComponentModel = ComponentModelConstructor
		<
			Design::GearBlank<GEAR_TYPE>,
			Design::TeethCutter<GEAR_TYPE>
		>()();

		try
		{
#if DEBUG_CONSOLE_OUTPUT
			/* Start measuring time... */
			auto Start = std::chrono::steady_clock::now();
#endif

			/* Construct updated model referenced by temporary component model pointer */
			std::future<std::unique_ptr<TopoDS_Shape>> tModelShapeFuture = tComponentModel->constructModel( this->getParameters() );

#if DEBUG_CONSOLE_OUTPUT
			std::cout << "Waiting for GEAR component model to be fully constructed..." << std::endl;
#endif

			/* Wait for the model to be fully constructed */
			tModelShapeFuture.wait();

#if DEBUG_CONSOLE_OUTPUT
			auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - Start );

			std::cout << "GEAR component model fully constructed in " << Duration.count() << " milliseconds using Thread Pool having " << Core::ThreadPool::get_mutable_instance().threadCount() << " worker threads." << std::endl;
#endif

			/* Construct shared_ptr out of the unique_ptr held in the model shape future */
			std::shared_ptr<TopoDS_Shape> tModelShape = std::move( tModelShapeFuture.get() );

			/* Once the temporary component model is fully constructed without any exceptions,
			 * swap the current model with the updated one */
			( this->getModel() ).swap( tModelShape );
		}
		catch( const Exception::Design::ModelConstructionFailed & Exception )
		{
			/* TODO: Improve error handling. It should not just to print out the error message... */
			std::cout << "Component::Gear (ModelConstructionFailed) -> Gear cannot be constructed. " << Exception.what() << std::endl;
		}
	}
}

#undef DEBUG_CONSOLE_OUTPUT
