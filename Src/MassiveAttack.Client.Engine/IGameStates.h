#ifndef __IGAMESTATES__
#define __IGAMESTATES__

class IGameStates {
public:
	virtual ~IGameStates() = default;
	virtual LEVELGEOMETRY* GetGeometry() = 0;
	virtual bool Init() = 0;
};

#endif