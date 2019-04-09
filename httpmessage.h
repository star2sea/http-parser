#ifndef __HTTP_MESSAGE_H
#define __HTTP_MESSAGE_H

#include "parser/http_parser.h"
#include <map>

namespace httpparser
{
	class HttpMessage
	{
	public:
		void setVersion(unsigned short major, unsigned short minor) { http_major_ = major; http_minor_ = minor; }
		void setKeepAlive(bool keepalive) { keep_alive_ = keepalive; }
		void setBody(const char *buf, size_t len) { body_ = std::move(std::string(buf, len)); }
		void setHeader(const std::string &k, const std::string &v) { headers_[k] = v; }
		void setStatus(unsigned int status_code) { status_code_ = status_code; }
		void setStatusStr(const char *buf, size_t len) { status_str_ = std::move(std::string(buf, len)); }
		void setMethod(unsigned int method) { method_ = method; }
		void setReqUrl(const char *buf, size_t len) { req_url_ = std::move(std::string(buf, len)); }

		std::string methodStr() const { return http_method_str(static_cast<http_method>(method_)); }
		std::string versionStr() const { char version[] = "HTTP/1.0"; version[5] = http_major_ + 48; version[7] = http_minor_ + 48; return version; }
		std::string statusStr() const { return http_status_str(static_cast<http_status>(status_code_)); }
		
		bool getKeepAlive() const { return keep_alive_; }
		std::string getBody() const { return body_; }
		std::string getReqUrl() const { return req_url_; }
		unsigned int getStatus() const { return status_code_; }

		void reset();

	protected:
		unsigned short http_major_;
		unsigned short http_minor_;
		bool keep_alive_;
		std::map<std::string, std::string> headers_;
		std::string body_;

		unsigned int method_; // request only
		std::string req_url_; // request only

		unsigned int status_code_; // response only
		std::string status_str_;   // response only
	};

	class HttpRequest : public HttpMessage
	{
	public:

	

	private:

	};

	class HttpResponse : public HttpMessage
	{
	private:
		
	};
	
}

#endif