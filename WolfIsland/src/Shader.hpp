#pragma once
#include "Prerequisites.hpp"
#include "GpuResource.hpp"

/// <summary>	Klasa reprezentująca program Shadera w pamięci GPU. </summary>
class Shader : public GpuResource
{
	friend class Renderer;

public:
	/// <summary>	Domyślny konstruktor. </summary>
	Shader();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader(const Shader &lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader(Shader &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony operator przypisania. </summary>
	///
	/// <param name="lhs">	Obiekt do przypisania. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader& operator=(Shader cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader& operator=(Shader &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor kompilujący i linkujący program Shadera z podprogramów. </summary>
	///
	/// <param name="vertexShader">  	Podprogram shadera wierzechołków. </param>
	/// <param name="fragmentShader">	Podprogram shadera fragmentów. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Shader(std::string vertexShader, std::string fragmentShader);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja kompilująca i linkująca program Shadera z podprogramów. </summary>
	///
	/// <param name="vertexShader">  	Podprogram shadera wierzechołków. </param>
	/// <param name="fragmentShader">	Podprogram shadera fragmentów. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::string vertexShader, std::string fragmentShader);

	/// <summary>	Funkcja czyszcząca obiekt shadera do stanu z przed inicializacji. </summary>
	void clear() override;

	/// <summary>	Domyślny destruktor. </summary>
	~Shader();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca lokację parametru shadera. </summary>
	///
	/// <param name="name">	Nazwa parametru. </param>
	///
	/// <returns>	Lokacja parametru. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GLint getLocation(std::string name);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar obiektu w pamięci GPU. </summary>
	///
	/// <returns>	Rozmiar obiektu w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;
};



