///-------------------------------------------------------------------------------------------------
// file:	src\VertexBuffer.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "GpuBuffer.hpp"
#include "VertexLayout.hpp"
#include "Renderer.hpp"

///------------------------------------------------------------------------------------------------
/// <summary>	Buffer for vertex. </summary>
///
/// <typeparam name="T">	Generic type parameter. </typeparam>
/// 
///------------------------------------------------------------------------------------------------
template <typename T>
class VertexBuffer : public GpuBuffer
{
public:
	/// <summary>	Defines an alias representing the layout. </summary>
	typedef T Layout;

	/// <summary>	Default constructor. </summary>
	VertexBuffer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>(const VertexBuffer<T>& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>(VertexBuffer<T>&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="cas">	The cas. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>& operator=(VertexBuffer<T> cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer<T>& operator=(VertexBuffer<T>&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="elements">	The elements. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// <param name="dynamic"> 	(Optional) True to dynamic. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexBuffer(std::uint32_t elements, Renderer &renderer, bool dynamic = false);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="elements">	The elements. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// <param name="dynamic"> 	(Optional) True to dynamic. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t elements, Renderer &renderer, bool dynamic = false);

	/// <summary>	Destructor. </summary>
	~VertexBuffer();
	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	The size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets entity size. </summary>
	///
	/// <returns>	The entity size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getEntitySize() const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets elements count. </summary>
	///
	/// <returns>	The elements count. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getElementsCount() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Adds lhsData. </summary>
	///
	/// <param name="lhsData"> 	Information describing the left hand side. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(const std::vector<typename T::Data>& lhsData, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Adds lhsData. </summary>
	///
	/// <param name="lhsData"> 	Information describing the left hand side. </param>
	/// <param name="position">	The position. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(const std::vector<typename T::Data>& lhsData, std::uint32_t position, 
		Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Adds rhsData. </summary>
	///
	/// <param name="rhsData"> 	[in,out] Information describing the right hand side. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(std::vector<typename T::Data>&& rhsData, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Adds rhsData. </summary>
	///
	/// <param name="rhsData"> 	[in,out] Information describing the right hand side. </param>
	/// <param name="position">	The position. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t add(std::vector<typename T::Data>&& rhsData, std::uint32_t position,
		Renderer& renderer);

private:
	/// <summary>	The position. </summary>
	std::uint32_t mPosition;
	/// <summary>	The elements. </summary>
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



