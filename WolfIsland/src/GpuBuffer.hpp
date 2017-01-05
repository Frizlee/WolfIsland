///-------------------------------------------------------------------------------------------------
// file:	src\GpuBuffer.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "GpuResource.hpp"

/// <summary>	Values that represent GPU buffer types. </summary>
enum class GpuBufferType
{
	VERTEX_BUFFER,
	COPY_WRITE_BUFFER,
	COPY_READ_BUFFER
};

/// <summary>	Buffer for gpu. </summary>
class GpuBuffer : public GpuResource
{
public:
	/// <summary>	Default constructor. </summary>
	GpuBuffer() = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="type">	The type. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer(GpuBufferType type);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Copy constructor. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer(const GpuBuffer &lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructor. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer(GpuBuffer &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer& operator=(const GpuBuffer &lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer& operator=(GpuBuffer &&rhs);

	/// <summary>	Destructor. </summary>
	virtual ~GpuBuffer() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets entity size. </summary>
	///
	/// <returns>	The entity size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual std::uint32_t getEntitySize() const = 0;;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the type. </summary>
	///
	/// <returns>	The type. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBufferType getType() const;

private:
	/// <summary>	The type. </summary>
	GpuBufferType mType;
	
};

