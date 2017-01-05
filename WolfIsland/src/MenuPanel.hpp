///-------------------------------------------------------------------------------------------------
// file:	src\MenuPanel.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "GuiObject.hpp"
#include "Slider.hpp"
#include <glm/vec2.hpp>


/// <summary>	Panel for editing the menu. </summary>
class MenuPanel : public GuiObject
{
public:
	/// <summary>	Default constructor. </summary>
	MenuPanel();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="guiSpriteSheet">  	The graphical user interface sprite sheet. </param>
	/// <param name="heightSliderText">	The height slider text. </param>
	/// <param name="widthSliderText"> 	The width slider text. </param>
	/// <param name="wolfSliderText">  	The wolf slider text. </param>
	/// <param name="hareSliderText">  	The hare slider text. </param>
	/// <param name="pos">			   	The position. </param>
	/// <param name="renderer">		   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	MenuPanel(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
		std::shared_ptr<class Text> heightSliderText, 
		std::shared_ptr<class Text> widthSliderText,
		std::shared_ptr<class Text> wolfSliderText,
		std::shared_ptr<class Text> hareSliderText, 
		const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="guiSpriteSheet">  	The graphical user interface sprite sheet. </param>
	/// <param name="heightSliderText">	The height slider text. </param>
	/// <param name="widthSliderText"> 	The width slider text. </param>
	/// <param name="wolfSliderText">  	The wolf slider text. </param>
	/// <param name="hareSliderText">  	The hare slider text. </param>
	/// <param name="pos">			   	The position. </param>
	/// <param name="renderer">		   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet,
		std::shared_ptr<class Text> heightSliderText,
		std::shared_ptr<class Text> widthSliderText,
		std::shared_ptr<class Text> wolfSliderText,
		std::shared_ptr<class Text> hareSliderText,
		const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Destructor. </summary>
	~MenuPanel();

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
	/// <summary>	Gets the values. </summary>
	///
	/// <returns>	The values. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::array<std::int32_t, 4> getValues() const;

private:

	/// <summary>	The position. </summary>
	glm::vec2 mPos;

	/// <summary>	Resources. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
	/// <summary>	The height slider. </summary>
	std::shared_ptr<Slider<std::int32_t>> mHeightSlider;
	/// <summary>	The width slider. </summary>
	std::shared_ptr<Slider<std::int32_t>> mWidthSlider;
	/// <summary>	The wolf slider. </summary>
	std::shared_ptr<Slider<std::int32_t>> mWolfSlider;
	/// <summary>	The hare slider. </summary>
	std::shared_ptr<Slider<std::int32_t>> mHareSlider;
};

