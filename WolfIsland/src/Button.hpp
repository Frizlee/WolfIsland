///-------------------------------------------------------------------------------------------------
// file:	src\Button.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "GuiObject.hpp"
#include <glm/vec2.hpp>

/// <summary>	A button. </summary>
class Button :	public GuiObject
{
public:
	/// <summary>	Default constructor. </summary>
	Button();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="guiSpriteSheet">	 	The graphical user interface sprite sheet. </param>
	/// <param name="spriteIndex">		 	Zero-based index of the sprite. </param>
	/// <param name="pressedSpriteIndex">	Zero-based index of the pressed sprite. </param>
	/// <param name="pos">				 	The position. </param>
	/// <param name="renderer">			 	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Button(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::int32_t spriteIndex,
		std::int32_t pressedSpriteIndex, const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="guiSpriteSheet">	 	The graphical user interface sprite sheet. </param>
	/// <param name="spriteIndex">		 	Zero-based index of the sprite. </param>
	/// <param name="pressedSpriteIndex">	Zero-based index of the pressed sprite. </param>
	/// <param name="pos">				 	The position. </param>
	/// <param name="renderer">			 	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::int32_t spriteIndex,
		std::int32_t pressedSpriteIndex, const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Destructor. </summary>
	~Button();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draws the given renderer. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Grab input. </summary>
	///
	/// <param name="orthoMatrix">	The ortho matrix. </param>
	/// <param name="app">		  	[in,out] The application. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the given deltaTime. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(double deltaTime) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a position. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::vec2& pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets automatic unpress. </summary>
	///
	/// <param name="state">	True to state. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setAutoUnpress(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is pressed. </summary>
	///
	/// <returns>	True if pressed, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isPressed() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets the press. </summary>
	///
	/// <param name="state">	True to state. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPress(bool state);

private:
	/// <summary>	True if pressed. </summary>
	bool mPressed;
	/// <summary>	True to automatically unpress. </summary>
	bool mAutoUnpress;

	/// <summary>	The position. </summary>
	glm::vec2 mPos;
	
	/// <summary>	Resources. </summary>
	std::int32_t mSpriteIndex;
	/// <summary>	Zero-based index of the pressed sprite. </summary>
	std::int32_t mPressedSpriteIndex;
	/// <summary>	The graphical user interface sprite sheet. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
};

