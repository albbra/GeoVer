#include <cogra/io/Log.h>

namespace cogra
{
namespace io
{
	namespace log
	{
		LogChannel info("info",LOG_CONSOLE);
		LogChannel debug("debug",LOG_DEBUG);
		LogChannel warning("warning",LOG_CONSOLE);
		LogChannel error("error",LOG_CONSOLE);
		LogChannel test("test",LOG_CONSOLE,LOG_FILE,"test.log");
	}
}
}