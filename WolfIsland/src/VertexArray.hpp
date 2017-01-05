///-------------------------------------------------------------------------------------------------
// file:	src\VertexArray.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "GpuResource.hpp"
#include "gl_core_3_3.hpp"

class VertexLayout;
class Renderer;
class GpuBuffer;
template <typename T>
class VertexBuffer;

/// <summary>	A vertex array. </summary>
class VertexArray : public GpuResource
{
public:
	/// <summary>	Default constructor. </summary>
	VertexArray();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Copy/Move constructors and assignments. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray(const VertexArray& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructor. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray(VertexArray&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="cas">	The cas. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray& operator=(VertexArray cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexArray& operator=(VertexArray&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="buffer">  	The buffer. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	template <typename T>
	VertexArray(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="buffer">  	The buffer. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	template <typename T>
	void create(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer);

	/// <summary>	Destructor. </summary>
	~VertexArray();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Adds an instance buffer to 'renderer'. </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="buffer">  	The buffer. </param>
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	template <typename T>
	void addInstanceBuffer(std::shared_ptr<VertexBuffer<T>> buffer, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the buffer. </summary>
	///
	/// <returns>	The buffer. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<GpuBuffer> getBuffer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets instance buffer. </summary>
	///
	/// <returns>	The instance buffer. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<GpuBuffer> getInstanceBuffer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets vertex size. </summary>
	///
	/// <returns>	The vertex size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getVertexSize() const;

	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the size. </summary>
	///
	/// <returns>	The size. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

private:
	/// <summary>	The buffer. </summary>
	std::shared_ptr<GpuBuffer> mBuffer;
	/// <summary>	Buffer for instance data. </summary>
	std::shared_ptr<GpuBuffer> mInstanceBuffer;
	/// <summary>	Number of vertex attributes. </summary>
	std::uint32_t mVertexAttribCount;
	/// <summary>	Number of instance attributes. </summary>
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

