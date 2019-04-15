#include "httpmessage.h"
#include <sstream>
using namespace httpparser;

void HttpMessage::reset()
{
	http_major_ = 1;
	http_minor_ = 1;

	keep_alive_ = false;
   
    headers_.clear();
    body_.clear();
    
    method_ = 0;
    req_url_.clear();
    
    status_code_ = 0;
    status_str_.clear();
}

std::string HttpMessage::headerStr() const
{
    std::ostringstream ostr;
    for (auto iter = headers_.cbegin(); iter != headers_.cend(); ++iter)
    {
        ostr << iter->first << ": " << iter->second << "\r\n";
    }
    return ostr.str();
}

std::string HttpRequest::toStr() const
{
    std::ostringstream ostr;
    ostr << methodStr() << " " << req_url_ << versionStr() << "\r\n";
    ostr << headerStr() << "\r\n";
    ostr << body_;
    return ostr.str();
}

std::string HttpResponse::toStr() const
{
    std::ostringstream ostr;
    ostr << versionStr() << " " << status_code_ << " " << statusStr() << "\r\n";
    ostr << headerStr() << "\r\n";
    ostr << body_;
    return ostr.str();
}
