#include <iostream>

#include <cogra/io/Log.h>

int main()
{
	// Log Something
	cogra::io::LOG(cogra::io::log::test,"test");
	
	// Log to different Channel
	cogra::io::LOG(cogra::io::log::info,"test");
	
	// Add Fileoutput to LogChannel
	cogra::io::log::info.add(cogra::io::log::LOG_FILE,"hmm.log");
	
	// Log more
	cogra::io::LOG(cogra::io::log::info,"test");
	cogra::io::LOG(cogra::io::log::info,"test {0} {2} {1}",1,2,3);
}