/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     logger.cpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../includes/core/core.hpp"

// extern Core    *g_core;

bl8		LogInit()
{
	return (true);
}

void	LogShutdown()
{

}

Platform	platform;

void	LogMessage(logLevel level, const char *message, ...)
{
	const char	*levelStr[6] = {"[*FATAL*]   : ", "[*ERROR*]   : ", "[*WARNING*] : ",
		"[*INFO*]    : ", "[*DEBUG*]   : ", "[*TRACE*]   : "};
	bl8 		shouldLog = level < LOG_LEVEL_WARNING;

	char outMessage[32000];
	std::memset(outMessage, 0, sizeof(outMessage));

	va_list args;
	va_start(args, message);
	vsnprintf(outMessage, 32000, message, args);
	va_end(args);

	std::string outBuffer = levelStr[level];
	outBuffer += outMessage;
	outBuffer += "\n";

	if (shouldLog)
	{
		platform.PlatconsoleWriteError(outBuffer, level);
	}
	else
	{
		platform.PlatconsoleWrite(outBuffer, level);
	}
}

// From Code/includes/core/assert.hpp
void	ReportAssertionFailure(std::string const expression, std::string const message,
							std::string const file, sint32 line)
{
	LogMessage(LOG_LEVEL_FATAL, "Assertion failed: %s, message: %s, file: %s, line: %d\n",
		expression.c_str(), message.c_str(), file.c_str(), line);
}
