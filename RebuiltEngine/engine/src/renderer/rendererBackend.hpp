/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 renderBackhand.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef RENDERBACKHAND_HPP
# define RENDERBACKHAND_HPP

# include "rendererTypes.inl"

struct platformState;

bl8		RendererBackendCreate(rendererBackendType type, struct platformState* platState,
			rendererBackend* outRendererBackend);
void	RendererBackenDestroy(rendererBackend* rendererBackend);

#endif
