#include "httpparser.h"
#include <string.h>
#include <iostream>
using namespace httpparser;

const char REQUEST[] =
"POST /post_identity_body_world?q=search#hey HTTP/1.1\r\n"
"Accept: */*\r\n"
"Transfer-Encoding: identity\r\n"
"Content-Length: 5\r\n"
"\r\n"
"World"
;


int main()
{
    HttpRequest req;
    HttpParser parser;
    parser.parser_init(&req, HTTP_REQUEST, [&](bool ret){
        if (ret)
            std::cout << "request: " << req.toStr() << std::endl;
        else
            std::cout << "parser request error" << std::endl;
    });
    parser.parse(REQUEST, strlen(REQUEST));
    
    HttpResponse resp;
    resp.setMethod(HTTP_GET);
	resp.setStatus(HTTP_STATUS_OK);
    resp.setHeader("test", 10);
    resp.setKeepAlive(true, true);
	resp.setBody(std::string("hello"), true);
    
    auto resp_str = resp.toStr();
    //std::cout << resp_str << std::endl;
    resp.reset();
    
    parser.parser_init(&resp, HTTP_RESPONSE, [&](bool ret){
        if (ret)
            std::cout << "response: " << resp.toStr() << std::endl;
        else
            std::cout << "parser response error" << std::endl;
    });

	parser.parse(resp_str.c_str(), resp_str.length());
	
	getchar();

    return 0;
}
