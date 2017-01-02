#pragma once

#ifdef MASSIVEATTACKENGINE_EXPORTS  
#define MASSIVEATTACKENGINE_API __declspec(dllexport)   
#else  
#define MASSIVEATTACKENGINE_API __declspec(dllimport)   
#endif  

namespace MassiveAttackClientEngine
{
	class MainEngine
	{
	public:
		static MASSIVEATTACKENGINE_API void RunEngine();

		static MASSIVEATTACKENGINE_API const char * GetAvailableGfxRenderers();
	};
}
