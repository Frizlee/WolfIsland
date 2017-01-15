#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include "Shader.hpp"


/// <summary>	
///		Klasa renderera odpowiadająca za rysowanie przymitywnych obiektów na scenie. 
/// </summary>
class Renderer
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Renderer();

	/// <summary>	Domyślny destrukotr. </summary>
	~Renderer();

	/// <summary>	
	///		Funkcja inicjalizująca obiekt renderera. Ustawia wszystkie potrzebne stany OpenGL
	/// </summary>
	void init();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja która ustawia anktualny obiekt Shadera. </summary>
	///
	/// <param name="shader">	Zlinkowany program Shadera do ustawienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindShader(class Shader& shader);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja ustawiająca aktualną teksturę w podanym miejscu. Z regóły miejsce 0 oznacza
	///		teksturę typu diffuse, ale zależy to od aktuanlnie używanego Shadera.
	/// </summary>
	///
	/// <param name="texture">	Tekstura do ustawienia. </param>
	/// <param name="slot">   	Miejsce na teksturę. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindTexture(class Texture& texture, std::int32_t slot);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja ustawiająca aktualne stany OpenGL, w których skład wchodzą m. in. używany
	///		bufor wierzchołków czy bufor indeksów.
	/// </summary>
	///
	/// <param name="arr">	[in,out] The array. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindVertexArray(class VertexArray &arr);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja ustawiająca aktualny bufor GPU. Typ bufora zostanie pobrany automatycznie 
	/// </summary>
	///
	/// <param name="buf">	Obiekt bufora GPU. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindBuffer(class GpuBuffer &buf);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca aktualny bufor GPU jako bufor o podanym typie. </summary>
	///
	/// <param name="buf"> 	Obiekt bufora GPU. </param>
	/// <param name="type">	Typ bufora. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindBuffer(class GpuBuffer &buf, enum class GpuBufferType &type);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca aktualną macież ortagonalną. </summary>
	///
	/// <param name="orthoMatrix">	Macież ortagonalna. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void bindOrthoMatrix(const glm::mat4& orthoMatrix);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca stan testu głębokości. </summary>
	///
	/// <param name="state">	Jeżeli prawda test będzie wykonywany, jeżeli fałsz - nie. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setDepthTest(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca widok OpenGL. </summary>
	///
	/// <param name="dimensions">	Rozmiary widoku. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setViewport(const glm::tvec2<std::int32_t>& dimensions);

	/// <summary>	Funkcja ustawiająca stany potrzebne do wykonania drawSprite(). </summary>
	void prepareDrawSprite();

	/// <summary>	Funkcja ustawiająca stany potrzebne do wykonania drawText(). </summary>
	void prepareDrawText();

	/// <summary>	
	///		Funkcja ustawiająca stany potrzebne do wykonania drawSpriteInstanced().
	/// </summary>
	void prepareDrawSpriteInstanced();

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja rysująca obiekt typu Sprite z podaną macierzą transformacji. Musi być 
	///		poprzedzona wywołaniem funkcji prepareDrawSprite();
	/// </summary>
	///
	/// <param name="sprite">		  	Obiekt Sprite. </param>
	/// <param name="transformMatrix">	Macierz transformacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void drawSprite(const class Sprite& sprite, const glm::mat4& transformMatrix);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja rysująca obiekt typu Text z podaną macierzą transformacji. Musi być 
	///		poprzedzona wywołaniem funkcji prepareDrawText();
	/// </summary>
	///
	/// <param name="text">			  	Obiekt Text. </param>
	/// <param name="transformMatrix">	Macierz transformacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void drawText(const class Text& text, const glm::mat4& transformMatrix);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja rysująca obiekty typu Sprite z podaną macierzą transformacji. 
	///		Musi być poprzedzona wywołaniem funkcji prepareDrawSpriteInstanced();
	/// </summary>
	///
	/// <param name="sprite">		  	Obiekt Sprite. </param>
	/// <param name="transformMatrix">	Macierz transformacji. </param>
	/// <param name="instances">		
	///		Ilość obiektów znajdujących się w buforze instancji. 
	/// </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void drawSpriteInstanced(const class Sprite& sprite, const glm::mat4& transformMatrix,
		std::uint32_t instances);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pytająca czy obiekt Renderera jest gotowy do pracy. </summary>
	///
	/// <returns>	
	///		Prawda jeśli obiekt jest już zinicjalizowany, fałsz w przeciwnym wypadku. 
	/// </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isInitialized() const;
	
private:
	/// <summary>	Wartości reprezentująca aktualnie rysowany typ obiektów. </summary>
	enum class Setup
	{
		SPRITE,
		TEXT,
		SPRITE_INSTANCED
	};

	/// <summary> Aktualnie rysowany typ obiektów. </summary>
	Setup mSetup;

	/// <summary>	
	///		Prawda jeśli obiekt jest już zinicjalizowany, fałsz w przeciwnym wypadku. 
	/// </summary>
	bool mInitialized;


	/// <summary>	Macierz ortagonalna. </summary>
	glm::mat4 mOrthoMatrix;

	/// <summary>	Obiekt Shadera tekstu. </summary>
	Shader mTextShader;

	/// <summary>	Obiekt Shadera spriteów. </summary>
	Shader mSpriteShader;

	/// <summary>	Obiekt Shadera instancjonowanych spriteów. </summary>
	Shader mSpriteInstancedShader;

	/// <summary>	Obiekt Shadera wody - aktualnie nieużywany. </summary>
	Shader mWaterShader;

	/// <summary>	Obiekt OpenGL samplera typu mipmap linear. (Filtrowanie trójliniowe) </summary>
	GLuint mSamplerMipmapLinear;

	/// <summary>	Obiekt OpenGL samplera typu linear. (Filtrowanie dwuliniowe) </summary>
	GLuint mSamplerLinear;

	/// <summary>	Lokacja macierzy ortagonalnej w shaderze spriteów. </summary>
	GLint mOrthographicMatrixLocationSprite;

	/// <summary>	Lokacja samplera w shaderze spriteów. </summary>
	GLint mSamplerLocationSprite;

	/// <summary>	Lokacja macierzy ortagonalnej w shaderze tekstu. </summary>
	GLint mOrthographicMatrixLocationText;

	/// <summary>	Lokacja samplera w shaderze tekstu. </summary>
	GLint mSamplerLocationText;

	/// <summary>	Lokacja koloru tekstu w shaderze tekstu. </summary>
	GLint mTextColorLocationText;
	
	/// <summary>	Lokacja macierzy ortagonalnej w shaderze instancjonowanych spriteów. </summary>
	GLint mOrthographicMatrixLocationSpriteInstanced;

	/// <summary>	Lokacja samplera w shaderze instancjonowanych spriteów. </summary>
	GLint mSamplerLocationSpriteInstanced;

	/// <summary>	Lokacja macierzy ortagonalnej w shaderze wody. </summary>
	GLint mOrthographicMatrixLocationWater;

	/// <summary>	Lokacja samplera w shaderze wody. </summary>
	GLint mSamplerLocationWater;

	/// <summary>	Lokacja przemieszczenia tekstury w shaderze wody. </summary>
	GLint mDisplacementLocationWater;
};



