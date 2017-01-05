///-------------------------------------------------------------------------------------------------
// file:	src\InformationPanel.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "GuiObject.hpp"
#include <glm/vec2.hpp>


/// <summary>	Panel for editing the information. </summary>
class InformationPanel : public GuiObject
{
public:
	/// <summary>	Default constructor. </summary>
	InformationPanel();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="guiSpriteSheet">	   	The graphical user interface sprite sheet. </param>
	/// <param name="wolfMaleCouterText">  	The wolf male couter text. </param>
	/// <param name="woflFemaleCouterText">	The wofl female couter text. </param>
	/// <param name="hareCouterText">	   	The hare couter text. </param>
	/// <param name="boulderCouterText">   	The boulder couter text. </param>
	/// <param name="bushCouterText">	   	The bush couter text. </param>
	/// <param name="pos">				   	The position. </param>
	/// <param name="renderer">			   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	InformationPanel(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
		std::shared_ptr<class Text> wolfMaleCouterText, 
		std::shared_ptr<class Text> woflFemaleCouterText,
		std::shared_ptr<class Text> hareCouterText,
		std::shared_ptr<class Text> boulderCouterText,
		std::shared_ptr<class Text> bushCouterText, 
		const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="guiSpriteSheet">	   	The graphical user interface sprite sheet. </param>
	/// <param name="wolfMaleCouterText">  	The wolf male couter text. </param>
	/// <param name="woflFemaleCouterText">	The wofl female couter text. </param>
	/// <param name="hareCouterText">	   	The hare couter text. </param>
	/// <param name="boulderCouterText">   	The boulder couter text. </param>
	/// <param name="bushCouterText">	   	The bush couter text. </param>
	/// <param name="pos">				   	The position. </param>
	/// <param name="renderer">			   	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet,
		std::shared_ptr<class Text> wolfMaleCouterText,
		std::shared_ptr<class Text> woflFemaleCouterText,
		std::shared_ptr<class Text> hareCouterText,
		std::shared_ptr<class Text> boulderCouterText,
		std::shared_ptr<class Text> bushCouterText,
		const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Destructor. </summary>
	~InformationPanel();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draws the given renderer. </summary>
	///
	/// <param name="renderer">	The renderer. </param>
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
	/// <summary>	Updates the counters. </summary>
	///
	/// <param name="counters">	The counters. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateCounters(const std::array<std::int32_t, 5>& counters, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a position. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::vec2& pos);

private:

	/// <summary>	The position. </summary>
	glm::vec2 mPos;

	/// <summary>	Resources. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
	/// <summary>	The wolf male couter text. </summary>
	std::shared_ptr<class Text> mWolfMaleCouterText;
	/// <summary>	The wolf female couter text. </summary>
	std::shared_ptr<class Text> mWolfFemaleCouterText;
	/// <summary>	The hare couter text. </summary>
	std::shared_ptr<class Text> mHareCouterText;
	/// <summary>	The boulder couter text. </summary>
	std::shared_ptr<class Text> mBoulderCouterText;
	/// <summary>	The bush couter text. </summary>
	std::shared_ptr<class Text> mBushCouterText;
};

