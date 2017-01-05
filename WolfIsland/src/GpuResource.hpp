///-------------------------------------------------------------------------------------------------
// file:	src\GpuResource.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include "Resource.hpp"

/// <summary>	A GPU resource. </summary>
class GpuResource : public Resource
{
	friend class Renderer;

public:	
	/// <summary>	Default constructor. </summary>
	GpuResource();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Can't be copied. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource(const GpuResource& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructor. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource(GpuResource&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource& operator=(const GpuResource& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource& operator=(GpuResource&& rhs);

	/// <summary>	Destructor. </summary>
	virtual ~GpuResource() = 0;

protected:
	/// <summary>	The identifier. </summary>
	GLuint mID;

private:

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the identifier. </summary>
	///
	/// <returns>	The identifier. </returns>
	///--------------------------------------------------------------------------------------------
	GLuint getID() const;
};

