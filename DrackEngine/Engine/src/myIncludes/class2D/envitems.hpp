/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    envitems.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef ENVITEM_HPP
# define ENVITEM_HPP

# include "props.hpp"

class EnvItems : public Props
{
	public:
		EnvItems();
		EnvItems(Vector2 pos, Vector2 size, int blocking, Color color,
				Texture2D texture, int nbr, std::string name);
		EnvItems(EnvItems const &src);
		~EnvItems(void);

		EnvItems	&operator=(EnvItems const &rhs);

	private:
};

#endif