#pragma once
#ifndef COGRA_IO_LOG_H
#define COGRA_IO_LOG_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/msvc_sink.h>



namespace cogra
{
namespace io
{
	namespace log
	{
		enum LogType
		{
			LOG_CONSOLE,
			LOG_FILE,
			LOG_DEBUG,
		};
		
		class LogChannel
		{
			private:
				std::shared_ptr<spdlog::logger> m_logger;
				std::shared_ptr<spdlog::sinks::dist_sink_mt> m_sinks;
			
				template<typename... Args>
				void buildLogChannel(LogType lt ,const Args &... args)
				{
					buildLogChannel(lt);
					buildLogChannel(args...);
				}
				
				template<typename... Args>
				void buildLogChannel(LogType lt)
				{
					switch(lt)
					{
						default:
						case LOG_CONSOLE:
						{
							auto sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
							m_sinks->add_sink(sink);
						}
						break;
						
						case LOG_DEBUG:
						{
							#if defined(_WIN32)
							auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
							#else
							auto sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
							#endif
							m_sinks->add_sink(sink);
						}
						break;
					}
				}
				
				template<typename... Args>
				void buildLogChannel(LogType lt, const char *fp, const Args &... args)
				{
					buildLogChannel(lt,fp);
					buildLogChannel(args...);
				}
				
				template<typename... Args>
				void buildLogChannel(LogType lt, const char *fp)
				{
					if(lt == LOG_FILE)
					{
						auto sink = std::make_shared<spdlog::sinks::simple_file_sink_mt>(fp);
						m_sinks->add_sink(sink);
					}
				}
			
			public:
				
				template<typename... Args>
				LogChannel(const char *name)
				{
					m_sinks = std::make_shared<spdlog::sinks::dist_sink_mt>();
					m_logger = std::make_shared<spdlog::logger>(name, m_sinks);
					m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] %v");
				}
				
				template<typename... Args>
				LogChannel(const char *name, const Args &... args) :
					LogChannel(name)
				{
					buildLogChannel(args...);
				}
				
				~LogChannel(void)
				{
					
				}
					
				template<typename... Args>
				void log(const char *fmt, const Args &... args)
				{
					m_logger->info(fmt,args...);
				}
						
				template<typename... Args>
				void log(const char *msg)
				{
					m_logger->info(msg);
				}
						
				template<typename T>
				void log(const T &msg)
				{
					m_logger->info(msg);
				}
				
				template<typename... Args>
				void add(const Args &... args)
				{
					buildLogChannel(args...);
				}
		};
		
		extern LogChannel info;
		extern LogChannel debug;
		extern LogChannel warning;
		extern LogChannel error;
		extern LogChannel test;
	}
	
	template<typename... Args>
	void LOG(cogra::io::log::LogChannel &channel, const char *fmt, const Args &... args)
	{
		channel.log(fmt,args...);
	}
	
	template<typename... Args>
	void LOG(cogra::io::log::LogChannel &channel, const char *msg)
	{
		channel.log(msg);
	}
	
	template<typename T>
	void LOG(cogra::io::log::LogChannel &channel, const T &msg)
	{
		channel.log(msg);
	}
}
}

#endif