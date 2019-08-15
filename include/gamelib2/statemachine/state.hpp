#pragma	once

#include	"../input/device.hpp"
#include	<string>

namespace	gamelib2	{

// base class for states
class	State	{
public:
				// construct / destruct
				State();
				virtual	~State();

				// state started
				virtual	void	start()	=	0;

				// main update
				virtual	void	update(const	float	dt)	=	0;

				// end
				virtual	void	end()	=	0;

				// check for end state
				virtual	bool	finished()	=	0;

				// change to next state
				virtual	void	changeToNextState()	=	0;

				// event handler
				virtual	void	handle_input(const	ControllerEvent	&event)	=	0;

				// identifier
				std::string	name;
};
}	// namespace gamelib2
