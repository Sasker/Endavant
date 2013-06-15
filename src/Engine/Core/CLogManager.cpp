#include "CLogManager.h"
#include <ctime>
#include "Utils/CXMLParserPUGI.h"
#include "Utils/CConversions.h"

using namespace std;



static const std::string LOG_CONFIG_XML_PATH("./Recursos/Config/log_options.xml");

CLogManager::CLogManager()
{
	m_IsLogEnabled = false;
}

CLogManager::~CLogManager()
{
	m_IsLogEnabled = false;
}

void	CLogManager::StartUp()
{
	m_Loggers.clear();

	CXMLParserPUGI Parser(LOG_CONFIG_XML_PATH);
	if (!Parser.Ready())
	{
		std::cout<< "[FATAL ERROR]FAILED LOADING LOGSYSTEM XML CONFIG " << LOG_CONFIG_XML_PATH << std::endl << std::flush;
		return;
	}

	u32 loggersCount = Parser.GetNodeNameCount("LOGSYSTEM/LOGGER");
	for ( u32 c = 0; c < loggersCount; c++ )
	{
		std::string LoggerNode("LOGSYSTEM/LOGGER#");
		LoggerNode += to_string( c );

		std::string l_Mode = Parser.GetStringAttributeValue( LoggerNode, "Mode");
		std::string l_Name = Parser.GetStringAttributeValue( LoggerNode, "Name");
		std::string l_Types = Parser.GetStringAttributeValue( LoggerNode, "Types");
		std::string l_Systems = Parser.GetStringAttributeValue( LoggerNode, "Systems");

		CLogType LoggerN;
		if ( l_Mode == "File" )
		{
			LoggerN.m_IsConsole = false;
			LoggerN.m_logfile = new std::ofstream();
			LoggerN.m_logfile->open( l_Name.c_str(), std::ios::app);
			if (!LoggerN.m_logfile->is_open())
			{
				delete LoggerN.m_logfile;
				continue;
			}
		}
		LoggerN.m_loglevel = ParseLogLevelOptions( l_Types );
		LoggerN.m_logsubsystem = ParseLogSubSystemOptions( l_Systems );
		m_Loggers.push_back( LoggerN );
	}

	if ( m_Loggers.size() > 0 )
		m_IsLogEnabled = true;


}

void	CLogManager::ShutDown()
{
	std::vector< CLogType >::iterator LoggerIt = m_Loggers.begin();
	while (LoggerIt != m_Loggers.end())
	{
		if (!LoggerIt->m_IsConsole)
		{
			delete LoggerIt->m_logfile;
		}
		LoggerIt++;
	}
	m_IsLogEnabled = false;
}

void	CLogManager::LogOutput(TLogLevel _level, TLogSubsystem _subs, std::string _msg, ... )
{
	if (m_IsLogEnabled)
	{
		char tmpbuffer[2048];
		va_list args;
		va_start (args, _msg);
		vsprintf (tmpbuffer,_msg.c_str(), args);
		va_end (args);

		std::string	l_msgbuffer;
		l_msgbuffer.clear();

		time_t t = time(0);   // get time now
		struct tm *now = localtime( &t );
		char buffer[128];
		sprintf( buffer, "[%02d:%02d:%02d] ", now->tm_hour, now->tm_min, now->tm_sec );
		l_msgbuffer+=buffer;

		switch (_subs)
		{
			case LOGSUB_VIDEO :
				l_msgbuffer+="[VIDEO]";
				break;
			case LOGSUB_INPUT :
				l_msgbuffer+="[INPUT]";
				break;
			case LOGSUB_PARSER:
				l_msgbuffer+="[PARSER]";
				break;
			case LOGSUB_GUI:
				l_msgbuffer+="[GUI]";
				break;
			case LOGSUB_GAME:
				l_msgbuffer+="[GAME]";
				break;
			case LOGSUB_SOUND:
				l_msgbuffer+="[SOUND]";
				break;
			case LOGSUB_ENGINE:
				l_msgbuffer+="[ENGINE]";
				break;
			case LOGSUB_EVENTS:
				l_msgbuffer+="[EVENT]";
				break;
			case LOGSUB_TIMER:
				l_msgbuffer+="[TIMER]";
				break;
			default:
				l_msgbuffer+="[UNDEF]";
				break;
		}

		switch(_level)
		{
			case LOG_DEVEL:
				l_msgbuffer+="[DEVEL] : ";
				break;
			case LOG_ERROR:
				l_msgbuffer+="[ERROR] : ";
				break;
			case LOG_INFO:
				l_msgbuffer+="[INFO] : ";
				break;
			case LOG_WARNING:
				l_msgbuffer+="[WARNING] : ";
				break;
			default:
				l_msgbuffer+="[UNDEF]";
				break;
		}

		WriteOutputLog(_level, _subs, l_msgbuffer+=tmpbuffer);
	}
}

void	CLogManager::WriteOutputLog(TLogLevel _level, TLogSubsystem _subs, std::string _msg)
{

	std::vector< CLogType >::iterator LoggerIt = m_Loggers.begin();
	while (LoggerIt != m_Loggers.end())
	{
		if ( (LoggerIt->m_loglevel & _level) && (LoggerIt->m_logsubsystem & _subs ) )
		{
			if (LoggerIt->m_IsConsole)
			{
				std::cout<< _msg <<std::endl << std::flush;
			}
			else
			{
				*(LoggerIt->m_logfile) << _msg << std::endl << std::flush;
			}
		}
		LoggerIt++;
	}

}

TLogLevel CLogManager::ParseLogLevelOptions(std::string strLogLevelOptions)
{
	TLogLevel l_LogLevel = LOG_NONE;
	std::vector<std::string> AllTokens;

	StringExplode( strLogLevelOptions, AllTokens, ',' );
	vector<string>::iterator TokenIt = AllTokens.begin();
	while (TokenIt != AllTokens.end())
	{
		if ( *TokenIt == "INFO" ) 		l_LogLevel = (TLogLevel)(l_LogLevel | LOG_INFO);
		if ( *TokenIt == "WARNING" ) 	l_LogLevel = (TLogLevel)(l_LogLevel | LOG_WARNING);
		if ( *TokenIt == "ERROR" ) 		l_LogLevel = (TLogLevel)(l_LogLevel | LOG_ERROR);
		if ( *TokenIt == "DEVEL" ) 		l_LogLevel = (TLogLevel)(l_LogLevel | LOG_DEVEL);
		if ( *TokenIt == "ALL" ) 		l_LogLevel = (TLogLevel)(l_LogLevel | LOG_ALL);
		TokenIt++;
	}

	return l_LogLevel;
}

TLogSubsystem CLogManager::ParseLogSubSystemOptions(std::string strLogSubSystemOptions)
{
	TLogSubsystem l_LogSubsystems = LOGSUB_NONE;
	std::vector<std::string> AllTokens;

	StringExplode( strLogSubSystemOptions, AllTokens, ',' );
	vector<string>::iterator TokenIt = AllTokens.begin();
	while (TokenIt != AllTokens.end())
	{
		if ( *TokenIt == "VIDEO" ) 	l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_VIDEO);
		if ( *TokenIt == "INPUT" ) 	l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_INPUT);
		if ( *TokenIt == "PARSER" ) l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_PARSER);
		if ( *TokenIt == "GUI" ) 	l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_GUI);
		if ( *TokenIt == "GAME" ) 	l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_GAME);
		if ( *TokenIt == "SOUND" ) 	l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_SOUND);
		if ( *TokenIt == "ENGINE" )	l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_ENGINE);
		if ( *TokenIt == "ALL" ) 	l_LogSubsystems = (TLogSubsystem)(l_LogSubsystems | LOGSUB_ALL);
		TokenIt++;
	}

	return l_LogSubsystems;
}
