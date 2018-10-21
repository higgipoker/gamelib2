#include	"spriteanimation.hpp"

namespace	gamelib2	{

// -----------------------------------------------------------------------------
// SpriteAnimation
// -----------------------------------------------------------------------------
SpriteAnimation::SpriteAnimation(std::string	a_id,	unsigned	int	a_frametime,
                                 bool	a_loop,
                                 std::vector<unsigned	int>	a_frames)
  :	name(std::move(a_id))
  ,	frames(std::move(std::move(a_frames)))
  ,	current_frame(frames.begin())
  ,	loop(a_loop)
  ,	frame_time(a_frametime)	{
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void	SpriteAnimation::start()	{
				current_frame	=	frames.begin();
				ticks	=	0;
				running	=	true;
}

// -----------------------------------------------------------------------------
// step
// -----------------------------------------------------------------------------
unsigned	int	SpriteAnimation::update()	{
				if	(running)	{
				    if	(++ticks	>	frame_time)	{
								    ticks	=	0;

												if	(++current_frame	==	frames.end())	{
												    if	(loop)	{
																    current_frame	=	frames.begin();
																}	else	{
																    running	=	false;
																				--current_frame;
																}
												}
								}
				}
				return	*current_frame;
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void	SpriteAnimation::stop()	{
				running	=	false;
}

// -----------------------------------------------------------------------------
// setStpeed
// -----------------------------------------------------------------------------
void	SpriteAnimation::setStpeed(unsigned	int	a_speed)	{
				frame_time	=	a_speed;
}

// -----------------------------------------------------------------------------
// currentFrame
// -----------------------------------------------------------------------------
unsigned	int	SpriteAnimation::currentFrame()	{
				return	*current_frame;
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool	SpriteAnimation::finished()	{
				if	(!loop)	{
				    return	!running;
				}
				return	false;
}

}	// namespace gamelib2
