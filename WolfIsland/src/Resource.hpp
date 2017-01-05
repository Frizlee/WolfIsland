///-------------------------------------------------------------------------------------------------
// file:	src\Resource.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"

/// <summary>	A resource. </summary>
class Resource
{
public:
	/// <summary>	Default constructor. </summary>
	Resource();
	
	/// <summary>	Destructor. </summary>
	virtual ~Resource() = 0;
	/// <summary>	Clears this object to its blank/initial state. </summary>
	virtual void clear() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	The size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual std::uint32_t getSize() const = 0;
};

