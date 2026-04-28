#ifndef __BaseEssentials_h__
#define __BaseEssentials_h__

namespace jb
{

struct BaseEssentials
{
	virtual ~BaseEssentials() = default;
	BaseEssentials &operator=(const BaseEssentials &) = delete;
};

} 

#endif
