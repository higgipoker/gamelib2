#pragma	once

#include	<string>
#include	<vector>

namespace	gamelib2	{

/**
	* @brief a sprite animatio is just a lst of frames and a speed
	*/
class	SpriteAnimation	{
public:
				SpriteAnimation(std::string	a_id,	unsigned	int	a_frametime,	bool	a_loop,
				                std::vector<unsigned	int>	a_frames);

				// start the animation
				void	start();

				// update anim
				unsigned	int	update();

				// stop animation
				void	stop();

				// set the frame update speed
				void	setStpeed(unsigned	int	a_seped);

				// get the current frame
				unsigned	int	currentFrame();

				// for non looping animations, is finished?
				bool finished();

				std::string	name;

private:
				// list of frame numbers
				std::vector<unsigned	int>	frames;

				// point to current frame
				std::vector<unsigned	int>::iterator	current_frame;

				// is a looping animation
				bool	loop	=	false;

				// animation is still running
				bool	running	=	false;

				// time of a frame
				unsigned	int	frame_time	=	0;

				// frame timer
				unsigned	int	ticks	=	0;
};
}	// namespace gamelib2
