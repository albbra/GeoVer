#include <cogra/gl/UniformBuffer.h>

namespace cogra
{
	namespace gl
	{
		UniformBuffer::UniformBuffer(void * data, uint32 size)
		{
			GL_SAFE_CALL(glGenBuffers(1, &m_bufferId));
			bind();
			GL_SAFE_CALL(glBufferData(GL_UNIFORM_BUFFER, size, data, BufferUsage::convert(BufferUsage::Enum::StaticDraw)));
			unbind();
		}

		UniformBuffer::UniformBuffer(UniformBuffer && other)
		{
			m_bufferId = other.m_bufferId;
			other.m_bufferId = 0;
		}

		UniformBuffer& UniformBuffer::operator=(UniformBuffer && other)
		{
			m_bufferId = other.m_bufferId;
			other.m_bufferId = 0;
			return *this;
		}

		UniformBuffer::~UniformBuffer()
		{
			if (m_bufferId != 0)
			{
				GL_SAFE_CALL_NO_THROW(glDeleteBuffers(1, &m_bufferId));
			}
		}

		uint32 UniformBuffer::getBufferId()
		{
			return m_bufferId;
		}

		void UniformBuffer::bind()
		{
			GL_SAFE_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_bufferId));
		}

		void UniformBuffer::unbind()
		{
			GL_SAFE_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));
		}
	}
}
