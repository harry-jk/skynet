
/*
	Copyright 2013 Skynet Project

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    http://www.apache.org/licenses/LICENSE-	2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include <iostream>
#include <string.h>
	//TODO Support MacOSX, using function close(fd);
#include <unistd.h>

#include <memory>

#include <arpa/inet.h>
#include <sys/socket.h>


int main(int argc, char const *argv[])
{
	int _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in _addr;
	memset(&_addr, 0x00, sizeof(_addr));
	_addr.sin_family = AF_INET;	
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_addr.sin_port = htons(8888);
	int len = sizeof(_addr);
	int isBind = bind(_sock, (struct sockaddr*) &_addr, len);
	std::cout << isBind << std::endl;
	close(_sock);
	return 0;
}