///-------------------------------------------------------------------------------------------------
// file:	src\GuiObject.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include <glm/mat4x4.hpp>
#include "gl_core_3_3.hpp"

/// <summary>	A graphical user interface object. </summary>
class GuiObject
{
public:
	/// <summary>	Default constructor. </summary>
	GuiObject();
	/// <summary>	Destructor. </summary>
	virtual ~GuiObject() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draws the given renderer. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void draw(class Renderer& renderer) const = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Grab input. </summary>
	///
	/// <param name="orthoMatrix">	The ortho matrix. </param>
	/// <param name="app">		  	[in,out] The application. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void grabInput(const glm::mat4& orthoMatrix, class Application& app) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the given deltaTime. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void update(double deltaTime) = 0;

protected:
};

