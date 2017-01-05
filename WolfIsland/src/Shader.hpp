///-------------------------------------------------------------------------------------------------
// file:	src\Shader.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "GpuResource.hpp"

/// <summary>	A shader. </summary>
class Shader : public GpuResource
{
	friend class Renderer;

public:
	/// <summary>	Default constructor. </summary>
	Shader();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Copy/Move constructors and assignments. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader(const Shader &lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructor. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader(Shader &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="cas">	The cas. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader& operator=(Shader cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader& operator=(Shader &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="vertexShader">  	The vertex shader. </param>
	/// <param name="fragmentShader">	The fragment shader. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader(std::string vertexShader, std::string fragmentShader);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="vertexShader">  	The vertex shader. </param>
	/// <param name="fragmentShader">	The fragment shader. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::string vertexShader, std::string fragmentShader);
	
	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear() override;
	/// <summary>	Destructor. </summary>
	~Shader();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets a location. </summary>
	///
	/// <param name="name">	The name. </param>
	///
	/// <returns>	The location. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GLint getLocation(std::string name);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	The size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;
};



