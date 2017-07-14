/*
 * Involute.h
 *
 *  Created on: 4. 5. 2017
 *      Author: martin
 */

#ifndef PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_INVOLUTE_H_
#define PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_INVOLUTE_H_

/* Standard library inclusions */

/* OpenCascade inclusions */
#include <gp_Pnt.hxx>
#include <TopoDS_Edge.hxx>

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
	class GEAR_EXPORT Involute
	{
	public:
		/* TODO: Try to eliminate Steps parameter */
		Involute( const double BaseCircleRadius, const double OutsideCircleRadius, short Steps = 20 );

		operator TopoDS_Edge( void ) const;

#define USE_STATIC_ENDPOINT_METHODS

#ifndef USE_STATIC_ENDPOINT_METHODS
		gp_Pnt getBaseEnd( void ) const;
		gp_Pnt getOuterEnd( void ) const;
#else
		static gp_Pnt getBaseEnd( const TopoDS_Edge& Edge );
		static gp_Pnt getOuterEnd( const TopoDS_Edge& Edge );
#endif

	protected:

	private:
		TopoDS_Edge mInvoluteEdge;
	};
}

#endif /* PLUGIN_GEARS_COMPONENT_GEAR_DESIGN_INVOLUTE_H_ */
