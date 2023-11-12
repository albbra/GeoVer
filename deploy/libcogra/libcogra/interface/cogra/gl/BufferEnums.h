#ifndef COGRA_GL_BUFFERENUMS_H_
#define COGRA_GL_BUFFERENUMS_H_

#include <glad/glad.h>

namespace cogra
{
	namespace gl
	{
		struct BufferUsage
		{
			enum Enum
			{
				StreamDraw,
				StreamRead,
				StreamCopy,
				StaticDraw,
				StaticRead,
				StaticCopy,
				DynamicDraw,
				DynamicRead,
				DynamicCopy,
				End
			};

			static GLenum convert(const BufferUsage::Enum x)
			{
				switch (x)
				{
				case StreamDraw:
					return GL_STREAM_DRAW;
				case StreamRead:
					return GL_STREAM_READ;
				case StreamCopy:
					return GL_STREAM_COPY;
				case StaticDraw:
					return GL_STATIC_DRAW;
				case StaticRead:
					return GL_STATIC_READ;
				case StaticCopy:
					return GL_STATIC_COPY;
				case DynamicDraw:
					return GL_DYNAMIC_DRAW;
				case DynamicRead:
					return GL_DYNAMIC_READ;
				case DynamicCopy:
					return GL_DYNAMIC_COPY;
				default:
					return GL_NONE;
				}
			}

			static Enum convert(const GLenum x)
			{
				switch (x)
				{
				case GL_STREAM_DRAW:
					return StreamDraw;
				case GL_STREAM_READ:
					return StreamRead;
				case GL_STREAM_COPY:
					return StreamCopy;
				case GL_STATIC_DRAW:
					return StaticDraw;
				case GL_STATIC_READ:
					return StaticRead;
				case GL_STATIC_COPY:
					return StaticCopy;
				case GL_DYNAMIC_DRAW:
					return DynamicDraw;
				case GL_DYNAMIC_READ:
					return DynamicRead;
				case GL_DYNAMIC_COPY:
					return DynamicCopy;
				default:
					return End;
				}
			}
		};
	}
}

#endif