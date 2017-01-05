///-------------------------------------------------------------------------------------------------
// file:	src\ImageAtlas.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "Image.hpp"
#include <glm/vec4.hpp>


/// <summary>	An image atlas. </summary>
class ImageAtlas : public Image
{
public:
	/// <summary>	Defines an alias representing the rectangle. </summary>
	typedef glm::tvec4<std::uint32_t> Rect;

	/// <summary>	Default constructor. </summary>
	ImageAtlas();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructors and assignments Non copyable. </summary>
	///
	/// <param name="lhs">	The left hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas(const ImageAtlas& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move constructor. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas(ImageAtlas &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Assignment operator. </summary>
	///
	/// <param name="cas">	The cas. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas& operator=(ImageAtlas cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Move assignment operator. </summary>
	///
	/// <param name="rhs">	[in,out] The right hand side. </param>
	///
	/// <returns>	A shallow copy of this object. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas& operator=(ImageAtlas &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Override constructors. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas(std::uint32_t width, std::uint32_t height, Format format, 
		const std::vector<uint8_t> &bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format,
		const std::vector<std::uint8_t> &bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	[in,out] The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas(std::uint32_t width, std::uint32_t height, Format format, 
		std::vector<uint8_t> &&bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// <param name="bytes"> 	[in,out] The bytes. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format,
		std::vector<std::uint8_t> &&bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas(std::uint32_t width, std::uint32_t height, Format format);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// <param name="format">	Describes the format to use. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format);
	
	/// <summary>	Destructor. </summary>
	~ImageAtlas();
	/// <summary>	Clears this object to its blank/initial state. </summary>
	void clear();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Inserts the given image. </summary>
	///
	/// <param name="img">	[in,out] The image. </param>
	///
	/// <returns>	A Rect. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Rect insert(Image &img);

private:
	/// <summary>	A node. </summary>
	struct Node
	{
		/// <summary>	The childs[ 2]. </summary>
		std::unique_ptr<Node> mChilds[2];
		/// <summary>	The rectangle. </summary>
		Rect mRect;
		/// <summary>	True to free. </summary>
		bool mFree;

		/// <summary>	Default constructor. </summary>
		Node();

		///----------------------------------------------------------------------------------------
		/// <summary>	Move constructors and assignments Non copyable. </summary>
		///
		/// <param name="lhs">	The left hand side. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Node(const Node &lhs) = delete;

		///----------------------------------------------------------------------------------------
		/// <summary>	Constructor. </summary>
		///
		/// <param name="rhs">	[in,out] The right hand side. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Node(Node &&rhs);

		///----------------------------------------------------------------------------------------
		/// <summary>	Assignment operator. </summary>
		///
		/// <param name="cas">	The cas. </param>
		///
		/// <returns>	A shallow copy of this object. </returns>
		/// 
		///----------------------------------------------------------------------------------------
		Node& operator=(const Node &cas) = delete;

		///----------------------------------------------------------------------------------------
		/// <summary>	Move assignment operator. </summary>
		///
		/// <param name="rhs">	[in,out] The right hand side. </param>
		///
		/// <returns>	A shallow copy of this object. </returns>
		/// 
		///----------------------------------------------------------------------------------------
		Node& operator=(Node &&rhs);

		///----------------------------------------------------------------------------------------
		/// <summary>	Alignment warning. </summary>
		///
		/// <param name="i">	Zero-based index of the. </param>
		/// 
		///----------------------------------------------------------------------------------------
		void* operator new(size_t i);

		///----------------------------------------------------------------------------------------
		/// <summary>	Object de-allocation operator. </summary>
		///
		/// <param name="p">	[in,out] If non-null, the p to delete. </param>
		///
		/// <returns>	The result of the operation. </returns>
		/// 
		///----------------------------------------------------------------------------------------
		void operator delete(void *p);

		///----------------------------------------------------------------------------------------
		/// <summary>	Inserts. </summary>
		///
		/// <param name="width"> 	The width. </param>
		/// <param name="height">	The height. </param>
		///
		/// <returns>	A Rect. </returns>
		/// 
		///----------------------------------------------------------------------------------------
		Rect insert(std::uint32_t width, std::uint32_t height);
	};

	/// <summary>	The root. </summary>
	std::unique_ptr<Node> mRoot;
};



