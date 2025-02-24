/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	 renderFronthand.hpp      *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef RENDERFRONTEND_HPP
# define RENDERFRONTEND_HPP

# include <renderer/rendererTypes.inl>
#include "rendererBackend.hpp"

#include "core/logger.hpp"
#include "core/deMemory.hpp"

struct static_mesh_data;
struct platformState;

class Renderer
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//

	public:
		Renderer(void);
		Renderer(const Renderer &src);
		Renderer &operator=(const Renderer &src);

		~Renderer(void);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

	public:
		bl8		RendererInit(uint64* memoryRequirement, void* state, const char* applicationName);
		void	RendererShutdown(void* state);

		void	RendererOnResized(uint16 width, uint16 height);

		bl8		RendererBeginFrame(fl32 deltaTime);
		bl8		RendererEndFrame(fl32 deltaTime);
		bl8		RendererDrawFrame(renderPacket *packet);

	//**********************************************************************//
	//**                        Private Variables                         **//
	//**********************************************************************//
	
	private:
		rendererBackend *_backend;
};

#endif
