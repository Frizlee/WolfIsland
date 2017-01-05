///-------------------------------------------------------------------------------------------------
// file:	src\Codec.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"

/// <summary>	Move it somewhere. </summary>
struct memorybuf : std::streambuf
{
	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="base">	[in,out] If non-null, the base. </param>
	/// <param name="size">	The size. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	memorybuf(char *base, std::ptrdiff_t size)
	{
		setg(base, base, base + size);
	}
};


/// <summary>	A codec. </summary>
class Codec
{
public:
	/// <summary>	Default constructor. </summary>
	Codec();
	/// <summary>	Destructor. </summary>
	virtual ~Codec() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Decodes. </summary>
	///
	/// <param name="input">	[in,out] The input. </param>
	/// <param name="res">  	[in,out] The resource. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void decode(std::istream &input, class Resource &res) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Encodes. </summary>
	///
	/// <param name="output">	[in,out] The output. </param>
	/// <param name="res">   	[in,out] The resource. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void encode(std::ostream &output, class Resource &res) = 0;

private:

};



