///-------------------------------------------------------------------------------------------------
// file:	src\Renderer.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include "Shader.hpp"


/// <summary>	A renderer. </summary>
class Renderer
{
public:
	/// <summary>	Default constructor. </summary>
	Renderer();
	/// <summary>	Destructor. </summary>
	~Renderer();

	/// <summary>	S this object. </summary>
	void init();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Consider using const references while not drunk. </summary>
	///
	/// <param name="shader">	[in,out] The shader. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindShader(class Shader& shader);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Bind texture. </summary>
	///
	/// <param name="texture">	[in,out] The texture. </param>
	/// <param name="slot">   	The slot. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindTexture(class Texture& texture, std::int32_t slot);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Bind vertex array. </summary>
	///
	/// <param name="arr">	[in,out] The array. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindVertexArray(class VertexArray &arr);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Bind buffer. </summary>
	///
	/// <param name="buf">	[in,out] The buffer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindBuffer(class GpuBuffer &buf);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Bind buffer. </summary>
	///
	/// <param name="buf"> 	[in,out] The buffer. </param>
	/// <param name="type">	[in,out] The type. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindBuffer(class GpuBuffer &buf, enum class GpuBufferType &type);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Bind ortho matrix. </summary>
	///
	/// <param name="orthoMatrix">	The ortho matrix. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindOrthoMatrix(const glm::mat4& orthoMatrix);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Tests set depth. </summary>
	///
	/// <param name="state">	True to state. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setDepthTest(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a viewport. </summary>
	///
	/// <param name="dimensions">	The dimensions. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setViewport(const glm::tvec2<std::int32_t>& dimensions);

	/// <summary>	Prepare draw sprite. </summary>
	void prepareDrawSprite();
	/// <summary>	Prepare draw text. </summary>
	void prepareDrawText();
	/// <summary>	Prepare draw sprite instanced. </summary>
	void prepareDrawSpriteInstanced();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draw sprite. </summary>
	///
	/// <param name="sprite">		  	The sprite. </param>
	/// <param name="transformMatrix">	The transform matrix. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void drawSprite(const class Sprite& sprite, const glm::mat4& transformMatrix);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draw text. </summary>
	///
	/// <param name="text">			  	The text. </param>
	/// <param name="transformMatrix">	The transform matrix. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void drawText(const class Text& text, const glm::mat4& transformMatrix);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draw sprite instanced. </summary>
	///
	/// <param name="sprite">		  	The sprite. </param>
	/// <param name="transformMatrix">	The transform matrix. </param>
	/// <param name="instances">	  	The instances. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void drawSpriteInstanced(const class Sprite& sprite, const glm::mat4& transformMatrix, 
		std::uint32_t instances);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is initialized. </summary>
	///
	/// <returns>	True if initialized, false if not. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isInitialized() const;
	
private:
	/// <summary>	True if initialized. </summary>
	bool mInitialized;

	/// <summary>	Values that represent setups. </summary>
	enum class Setup
	{
		SPRITE,
		TEXT,
		SPRITE_INSTANCED
	} mSetup;

	/// <summary>	The ortho matrix. </summary>
	glm::mat4 mOrthoMatrix;

	/// <summary>	The text shader. </summary>
	Shader mTextShader;
	/// <summary>	The sprite shader. </summary>
	Shader mSpriteShader;
	/// <summary>	The sprite instanced shader. </summary>
	Shader mSpriteInstancedShader;
	/// <summary>	The water shader. </summary>
	Shader mWaterShader;

	/// <summary>	The sampler mipmap linear. </summary>
	GLuint mSamplerMipmapLinear;
	/// <summary>	The sampler linear. </summary>
	GLuint mSamplerLinear;

	/// <summary>	The orthographic matrix location sprite. </summary>
	GLint mOrthographicMatrixLocationSprite;
	/// <summary>	The sampler location sprite. </summary>
	GLint mSamplerLocationSprite;

	/// <summary>	The orthographic matrix location text. </summary>
	GLint mOrthographicMatrixLocationText;
	/// <summary>	The sampler location text. </summary>
	GLint mSamplerLocationText;
	/// <summary>	The text color location text. </summary>
	GLint mTextColorLocationText;
	
	/// <summary>	The orthographic matrix location sprite instanced. </summary>
	GLint mOrthographicMatrixLocationSpriteInstanced;
	/// <summary>	The sampler location sprite instanced. </summary>
	GLint mSamplerLocationSpriteInstanced;

	/// <summary>	The orthographic matrix location water. </summary>
	GLint mOrthographicMatrixLocationWater;
	/// <summary>	The sampler location water. </summary>
	GLint mSamplerLocationWater;
	/// <summary>	The displacement location water. </summary>
	GLint mDisplacementLocationWater;
};



