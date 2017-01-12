#pragma once
#include "Prerequisites.hpp"
#include "GpuBuffer.hpp"
#include "VertexLayout.hpp"
#include "Renderer.hpp"

///------------------------------------------------------------------------------------------------
/// <summary>	Klasa reprezentująca bufor wierzchołków w pamięci karty graficznej. </summary>
///
/// <typeparam name="T">	
/// 	Typ danych umieszczanych w buforze. Musi dziedziczyć po Klasie 
/// 	VertexLayout
/// </typeparam>
/// 
///------------------------------------------------------------------------------------------------
template <typename T>
class VertexBuffer : public GpuBuffer
{
public:
	/// <summary>	
	/// 	Definiuje typ Layout reprezentujący typ danych umieszczonych w aktualnym 
	///		obiekcie. 
	///	</summary>
	typedef T Layout;

	/// <summary>	Domyślny konstruktor. </summary>
	VertexBuffer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>(const VertexBuffer<T>& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>(VertexBuffer<T>&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony operator przypisania. </summary>
	///
	/// <param name="cas">	Obiekt do przypisania. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>& operator=(VertexBuffer<T> cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>& operator=(VertexBuffer<T>&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący bufor na podaną ilość elementów. </summary>
	///
	/// <param name="elements">	Maksymalna ilość elementów w buforze. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// <param name="dynamic"> 	
	/// 	[Opt] Jeżeli prawda, obiekt bufora jest dynamiczny (szybciej 
	/// 	obsługuje zmiany zawartości). 
	/// </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer(std::uint32_t elements, Renderer &renderer, bool dynamic = false);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca bufor na podaną ilość elementów. </summary>
	///
	/// <param name="elements">	Maksymalna ilość elementów w buforze. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// <param name="dynamic"> 	
	/// 	[Opt] Jeżeli prawda, obiekt bufora jest dynamiczny (szybciej 
	/// 	obsługuje zmiany zawartości). 
	/// </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t elements, Renderer &renderer, bool dynamic = false);

	/// <summary>	Domyślny destruktor. </summary>
	~VertexBuffer();

	/// <summary>	Czyści obiekt bufora do stanu z przed inicializacji. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar bufora w pamięci karty graficznej. </summary>
	///
	/// <returns>	Rozmiar bufora w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar encji (jednego elementu bufora) </summary>
	///
	/// <returns>	Rozmiar encji w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getEntitySize() const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca ilość elementów w buforze. </summary>
	///
	/// <returns>	Ilość elementów. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getElementsCount() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja kopiująca dane do bufora w pamięci karty graficzenej. </summary>
	///
	/// <param name="lhsData"> 	Dane do skopiowania do pamięci karty graficznej. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	///
	/// <returns>	Pozycja danych w buforze. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(const std::vector<typename T::Data>& lhsData, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Funkcja kopiująca dane do bufora w pamięci karty graficzenej na
	/// 	wyszczególnionej pozycji. 
	/// </summary>
	///
	/// <param name="lhsData"> 	Dane do skopiowania do pamięci karty graficznej. </param>
	/// <param name="position"> Miejsce do którego mają zostać skopiowane dane. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	///
	/// <returns>	Pozycja danych w buforze. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(const std::vector<typename T::Data>& lhsData, std::uint32_t position,
		Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja kopiująca dane do bufora w pamięci karty graficzenej. </summary>
	///
	/// <param name="lhsData"> 	Dane do skopiowania do pamięci karty graficznej. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	///
	/// <returns>	Pozycja danych w buforze. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(std::vector<typename T::Data>&& rhsData, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Funkcja kopiująca dane do bufora w pamięci karty graficzenej na
	/// 	wyszczególnionej pozycji. 
	/// </summary>
	///
	/// <param name="lhsData"> 	Dane do skopiowania do pamięci karty graficznej. </param>
	/// <param name="position"> Miejsce do którego mają zostać skopiowane dane. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	///
	/// <returns>	Pozycja danych w buforze. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(std::vector<typename T::Data>&& rhsData, std::uint32_t position,
		Renderer& renderer);

private:
	/// <summary>	Ostatnia pozycja bufora. </summary>
	std::uint32_t mPosition;
	/// <summary>	Ilość elementów. </summary>
	std::uint32_t mElements;
};

template<typename T>
inline VertexBuffer<T>::VertexBuffer()
	: GpuBuffer(GpuBufferType::VERTEX_BUFFER), mPosition{ 0 }
{
	static_assert(std::is_base_of<VertexLayout, T>(), "VertexBuffer must operate on VertexLayout");
}

template<typename T>
inline VertexBuffer<T>::VertexBuffer(VertexBuffer<T>&& rhs)
	: GpuBuffer(move(rhs))
{
	swap(mPosition, rhs.mPosition);
}

template<typename T>
inline VertexBuffer<T>& VertexBuffer<T>::operator=(VertexBuffer<T>&& rhs)
{
	GpuBuffer::operator=(move(rhs));
	swap(mPosition, rhs.mPosition);
	return *this;
}

template<typename T>
inline VertexBuffer<T>::VertexBuffer(std::uint32_t elements, Renderer& renderer, bool dynamic)
	: GpuBuffer(GpuBufferType::VERTEX_BUFFER), mPosition{ 0 }
{
	static_assert(std::is_base_of<VertexLayout, T>(), "VertexBuffer must operate on VertexLayout");
	create(elements, renderer, dynamic);
}

template<typename T>
inline void VertexBuffer<T>::create(std::uint32_t elements, Renderer& renderer, bool dynamic)
{
	gl::GenBuffers(1, &mID);
	renderer.bindBuffer(*this);
	mElements = elements;
	gl::BufferData(gl::ARRAY_BUFFER, elements * T::Size(), nullptr, 
		dynamic ? gl::DYNAMIC_DRAW : gl::STATIC_DRAW);
}

template<typename T>
inline VertexBuffer<T>::~VertexBuffer()
{
	gl::DeleteBuffers(1, &mID);
}

template<typename T>
inline void VertexBuffer<T>::clear()
{
	mPosition = 0;
}

template<typename T>
inline std::uint32_t VertexBuffer<T>::getSize() const
{
	return mElements * T::Size();
}

template<typename T>
inline std::uint32_t VertexBuffer<T>::getEntitySize() const
{
	return T::Size();
}

template<typename T>
inline std::uint32_t VertexBuffer<T>::getElementsCount() const
{
	return mElements;
}

template<typename T>
inline std::uint32_t VertexBuffer<T>::add(const std::vector<typename T::Data>& lhsData, 
	Renderer& renderer)
{
	std::uint32_t currentPos = mPosition;

	renderer.bindBuffer(*this);
	gl::BufferSubData(gl::ARRAY_BUFFER, mPosition, lhsData.size() * T::Size(), lhsData.data());
	mPosition += lhsData.size() * T::Size();

	return currentPos;
}

template<typename T>
inline std::uint32_t VertexBuffer<T>::add(const std::vector<typename T::Data>& lhsData,
	std::uint32_t position, Renderer& renderer)
{
	renderer.bindBuffer(*this);
	gl::BufferSubData(gl::ARRAY_BUFFER, position, lhsData.size() * T::Size(), lhsData.data());

	return position;
}

template<typename T>
inline std::uint32_t VertexBuffer<T>::add(std::vector<typename T::Data>&& rhsData, 
	Renderer& renderer)
{
	std::uint32_t currentPos = mPosition;

	renderer.bindBuffer(*this);
	gl::BufferSubData(gl::ARRAY_BUFFER, mPosition, rhsData.size() * T::Size(), rhsData.data());
	mPosition += rhsData.size() * T::Size();

	return currentPos;
}

template<typename T>
inline std::uint32_t VertexBuffer<T>::add(std::vector<typename T::Data>&& rhsData, 
	std::uint32_t position, Renderer& renderer)
{
	renderer.bindBuffer(*this);
	gl::BufferSubData(gl::ARRAY_BUFFER, position, rhsData.size() * T::Size(), rhsData.data());

	return position;
}



