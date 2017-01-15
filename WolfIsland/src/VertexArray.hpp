#pragma once
#include "Prerequisites.hpp"
#include "GpuResource.hpp"
#include "gl_core_3_3.hpp"

class VertexLayout;
class Renderer;
class GpuBuffer;
template <typename T>
class VertexBuffer;

/// <summary>	
///		Klasa reprezentująca tablicę stanów OpenGL wraz z przypisanymi buforami i formatem wierzchołków
/// </summary>
class VertexArray : public GpuResource
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	VertexArray();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray(const VertexArray& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray(VertexArray&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony operator przypisania. </summary>
	///
	/// <param name="lhs">	Obiekt do przypisania. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray& operator=(VertexArray cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray& operator=(VertexArray&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Konstruktor tworzący tablicę stanów odpowiadającom danemu buforowi wierzchołków. 
	/// </summary>
	///
	/// <typeparam name="T">	Typ danych bufora wierzchołków. </typeparam>
	/// <param name="buffer">  	Bufor wierzchołków. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	template <typename T>
	VertexArray(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja tworząca tablicę stanów odpowiadającom danemu buforowi wierzchołków. 
	/// </summary>
	///
	/// <typeparam name="T">	Typ danych bufora wierzchołków. </typeparam>
	/// <param name="buffer">  	Bufor wierzchołków. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	template <typename T>
	void create(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer);

	/// <summary>	Domyślny destruktor. </summary>
	~VertexArray();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Dodaje bufor instancji do tablisy stanów. </summary>
	///
	/// <typeparam name="T">	Typ danych bufora instancji. </typeparam>
	/// <param name="buffer">  	BUfor instancji. Jest to także bufor wierzchołków. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	template <typename T>
	void addInstanceBuffer(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca obiekt bufora wierzchołków. </summary>
	///
	/// <returns>	Wskaźnik na bufor wierzchołków. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<GpuBuffer> getBuffer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	FUnkcja zwracająca obiekt bufora instancji. </summary>
	///
	/// <returns>	Wskaźnik na bufor instancji. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<GpuBuffer> getInstanceBuffer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar jedneko wierzchołka. </summary>
	///
	/// <returns>	Rozmiar wierzchołka w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getVertexSize() const;

	/// <summary>	
	///		Funkcja czyszcząca obiekt tablicy stanów do stanu z przed inicializacji. 
	/// </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar obiektu w pamięci GPU. </summary>
	///
	/// <returns>	Rozmiar w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

private:
	/// <summary>	Wskaźnik na bufor wierzchołków. </summary>
	std::shared_ptr<GpuBuffer> mBuffer;

	/// <summary>	Wskaźnik na bufor instancji. </summary>
	std::shared_ptr<GpuBuffer> mInstanceBuffer;

	/// <summary>	Ilość atrybutów w danych wierzchołka. </summary>
	std::uint32_t mVertexAttribCount;

	/// <summary>	Ilość atrybutów w danych instancji. </summary>
	std::uint32_t mInstanceAttribCount;

};


template <typename T>
VertexArray::VertexArray(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer)
	: mVertexAttribCount{ 0 }, mInstanceAttribCount{ 0 }
{
	create(buffer, renderer);
}

template <typename T>
void VertexArray::create(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer)
{
	mBuffer = std::dynamic_pointer_cast<GpuBuffer>(buffer);

	gl::GenVertexArrays(1, &mID);
	T layout;
	renderer.bindVertexArray(*this);
	renderer.bindBuffer(*buffer);
	std::uint32_t i = 0;

	for (auto it : layout.getFormats())
	{
		if (it.empty)
			gl::DisableVertexAttribArray(i);
		else
		{
			gl::EnableVertexAttribArray(i);
			gl::VertexAttribPointer(i, it.size, it.type, it.normalized, it.stride,
				reinterpret_cast<void*>(it.pointer));
		}

		i++;
	}

	mVertexAttribCount = i;
}

template<typename T>
inline void VertexArray::addInstanceBuffer(std::shared_ptr<VertexBuffer<T>> buffer, 
	Renderer& renderer)
{
	mInstanceBuffer = std::dynamic_pointer_cast<GpuBuffer>(buffer);

	T layout;
	renderer.bindVertexArray(*this);
	renderer.bindBuffer(*buffer);

	std::uint32_t i = mVertexAttribCount;


	for (auto it : layout.getFormats())
	{
		if (it.empty)
			gl::DisableVertexAttribArray(i);
		else
		{
			gl::EnableVertexAttribArray(i);
			gl::VertexAttribPointer(i, it.size, it.type, it.normalized, it.stride,
				reinterpret_cast<void*>(it.pointer));
			gl::VertexAttribDivisor(i, 1);
		}

		i++;
	}
	mInstanceAttribCount = i - mVertexAttribCount;
}

