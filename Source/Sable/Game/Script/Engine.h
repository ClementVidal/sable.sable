#ifndef _SABLE_GAME_SCRIPT_ENGINE_
#define _SABLE_GAME_SCRIPT_ENGINE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

extern "C" 
{
#include <Sable\Game\Script\Lua\Lua.h>
}

namespace Sable
{

class CClassDescriptorBase;

/**  
\ingroup Game
GameObject
*/
class CScriptEngine : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CScriptEngine );

public:

	/** @name DataType */
	//@{
	//@}

	/** @name Constructor/destructor */
	//@{
	CScriptEngine();
	~CScriptEngine();
	//@}

	/** @name Accessors*/
	//@{
	Bool	Execute( String code );
	//@}

	/** @name Manipulator*/
	//@{
	static CClassDescriptorBase* ClassList;
	//@}

private:

	// Types

    // Methods

	// Static Method
	static Void* Alloc(void *ud, void *ptr, size_t osize, size_t nsize);

	// Static Attributes

    // Attributes
	lua_State*	m_State;
};

}

#endif
