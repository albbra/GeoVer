#ifndef _COGRA_GL_UNIFORM_BUFFER_H_
#define _COGRA_GL_UNIFORM_BUFFER_H_

#include <cogra/types.h>
#include <cogra/gl/OpenGLRuntimeError.h>
#include <cogra/gl/BufferEnums.h>


namespace cogra
{
	namespace gl
	{
		class UniformBuffer
		{
		public:
			UniformBuffer(void* data, uint32 size);

			UniformBuffer(const UniformBuffer&) = delete;
			UniformBuffer& operator=(const UniformBuffer&) = delete;

			UniformBuffer(UniformBuffer&& other);
			UniformBuffer& operator=(UniformBuffer&& other);

			~UniformBuffer();

			uint32 getBufferId();

			void bind();
			void unbind();
		private:
			uint32 m_bufferId;
		};
	}
}

#endif