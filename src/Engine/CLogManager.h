#ifndef CLOGMANAGER_H_
#define CLOGMANAGER_H_

enum TLogLevel
{
	LOG_NONE 	= 0,
	LOG_INFO 	= 1 << 0,
	LOG_WARNING = 1 << 1,
	LOG_ERROR	= 1 << 2,

	LOG_DEVEL	= 0x8000,		//Tipos de info, warning o error que se necesiten para desarrollar, luego no apareceran en version Release.
	LOG_ALL 	= 0xFFFF
};

enum TLogSubsystem
{
	LOGSUB_NONE 	= 0,
	LOGSUB_VIDEO 	= 1 << 0,
	LOGSUB_INPUT 	= 1 << 1,
	LOGSUB_PARSER 	= 1 << 2,
	LOGSUB_GUI 		= 1 << 3,
	LOGSUB_GAME 	= 1 << 4,
	LOGSUB_SOUND 	= 1 << 5,
	LOGSUB_ENGINE 	= 1 << 6,
	LOGSUB_EVENTS	= 1 << 7,
	LOGSUB_TIMER	= 1 << 8,
	LOGSUB_RESOURCES= 1 << 9,

	LOGSUB_ALL		= 0xFFFF
};


#include <vector>
#include <iostream>
#include <cstdarg>
#include <string>
#include <fstream>
#include "CBaseEngine.h"
#include "Defines.h"

class CLogManager
{
public:

	void 	LogOutput(TLogLevel, TLogSubsystem, std::string, ...);

	void	StartUp();
	void	ShutDown();

	bool	m_IsLogEnabled;

	~CLogManager();
	CLogManager();	friend class CoreEngine;
private:

	struct LogType{
		std::ofstream	*m_logfile;
		bool			m_IsConsole;
		TLogLevel		m_loglevel;
		TLogSubsystem	m_logsubsystem;

		LogType():m_logfile(NULL),m_IsConsole(true),m_loglevel(LOG_NONE),m_logsubsystem(LOGSUB_NONE) {};
	};

	std::vector< LogType >	m_Loggers;
	inline	void	WriteOutputLog(TLogLevel, TLogSubsystem, std::string);

	TLogLevel		ParseLogLevelOptions( std::string);
	TLogSubsystem	ParseLogSubSystemOptions( std::string);
};

#endif /* CLOGMANAGER_H_ */

