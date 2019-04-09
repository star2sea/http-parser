#include "httpparser.h"
#include <assert.h>
using namespace httpparser;
void HttpParser::parser_init(HttpMessage *msg, enum http_parser_type type, const ParseDoneCallback & cb)
{
	http_parser_init(&parser_, type);
	
	http_parser_settings_init(&settings_);

	settings_.on_message_begin = on_message_begin;
	settings_.on_headers_complete = on_headers_complete;
	settings_.on_message_complete = on_message_complete;

	settings_.on_header_field = on_header_field;
	settings_.on_header_value = on_header_value;
	settings_.on_url = on_request_url;
	settings_.on_status = on_response_status;
	settings_.on_body = on_body;

	message_ = msg;
	parseDoneCallback_ = cb;
}
size_t HttpParser::parse(const char *buf, size_t len)
{
	size_t parsed = http_parser_execute(&parser_, &settings_, buf, len);
	if (parsed != len)
	{
		parseDoneCallback_(false);
	}
	return parsed;
}

int HttpParser::message_begin_cb()
{
	message_->reset();
	return 0;
}

int HttpParser::headers_complete_cb()
{
	if (!header_.empty())
	{
		message_->setHeader(header_, value_);
	}
	header_.clear();
	value_.clear();

	message_->setMethod(parser_.method);
	message_->setVersion(parser_.http_major, parser_.http_minor);
	message_->setStatus(parser_.status_code);
	message_->setKeepAlive(http_should_keep_alive(&parser_));
	return 0;
}

int HttpParser::message_complete_cb()
{
	if (parseDoneCallback_)
		parseDoneCallback_(true);
	return 0;
}

int HttpParser::header_field_cb(const char *buf, size_t len)
{
	if (!value_.empty())
	{
		assert(!header_.empty());
		message_->setHeader(header_, value_);
		header_.clear();
		value_.clear();
	}
	else
	{
		header_.append(buf, len);
	}
	return 0;
}

int HttpParser::header_value_cb(const char *buf, size_t len)
{
	value_.append(buf, len);
	return 0;
}

int HttpParser::request_url_cb(const char *buf, size_t len)
{
	message_->setReqUrl(buf, len);
	return 0;
}

int HttpParser::response_status_cb(const char *buf, size_t len)
{
	message_->setStatusStr(buf, len);
	return 0;
}

int HttpParser::body_cb(const char *buf, size_t len)
{
	message_->setBody(buf, len);
	return 0;
}