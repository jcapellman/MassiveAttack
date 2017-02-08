#ifndef __IGAMESTATES__
#define __IGAMESTATES__

class IGameStates {
public:
	virtual ~IGameStates() = default;
	virtual void Render() = 0;
};

#endif