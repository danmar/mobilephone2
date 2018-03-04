
all:	sms-list	sms-send	dial

sms-list:	sms-list.cpp	../gsminterface.h	../gsminterface.cpp
	g++ -I.. -o sms-list sms-list.cpp ../gsminterface.cpp

sms-send:	sms-send.cpp	../gsminterface.h	../gsminterface.cpp
	g++ -I.. -o sms-send sms-send.cpp ../gsminterface.cpp

dial:	dial.cpp	../gsminterface.h	../gsminterface.cpp
	g++ -I.. -o dial dial.cpp ../gsminterface.cpp
