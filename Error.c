#include "Error.h"

const char* getMsgByErrcode(error_code_t errcode);
void initDebugLog(const char* dbg_log);
const char* getMsgStr(msg_t msgtype);

const char* _setColor(int ground, int attrib, int color) {
	char buff[16] = {0};
    snprintf(buff, 15, "\033[%d;%dm", attrib, (ground * 10) + color);
    return buff;
}

const char* getMsgByErrcode(error_code_t errcode) {
	switch(errcode) {
	case _errcode_usage:
		return ERRCODE_USAGE_MSG;

	case _errcode_clean:
		return ERRCODE_CLEAN_MSG;
		
	case _errcode_unknown:
		return ERRCODE_UNKOWN_MSG;
		
	case _errcode_log_error:
		return ERRCODE_LOG_MSG;

	case _errcode_IO:
		return ERRCODE_IO_MSG;
	}
	return "";
}

void _exitWithError(const char* file, const char* func, unsigned int line, error_code_t errcode, const char* format, ...) {
	char buff[2048] = {0};
	va_list val;
	va_start(val, format);
	snprintf(buff, 2048, "\n  Error Raised:\n  >> %s - %s.\n", getMsgByErrcode(errcode), format);
	vfprintf(stdout, buff, val);
	_logger_write(file, func, line, msg_t_fatal, buff);
	va_end(val);
	exit(errcode);
}

void setTColorByMsgType(msg_t msgtype) {
	switch(msgtype) {
	case msg_t_error:
		fprintf(stderr, "%s", setColor(Red));
		break;
	case msg_t_warning:
		fprintf(stderr, "%s", setColor(Yellow));
		break;
	case msg_t_message:
		fprintf(stderr, "%s", setColor(Green));
		break;
	case msg_t_debug:
		fprintf(stderr, "%s", setColor(Blue));
		break;
	case msg_t_fatal:
		fprintf(stderr, "%s", _setColor(FG, _ATTR_UNDERSCORE, Red));
		break;
	case msg_t_none:
	default:
		fprintf(stderr, "%s", ColorReset);
	}
}

const char* getMsgStr(msg_t msgtype) {
	switch(msgtype) {
	case msg_t_error:
		return "ERROR";
	case msg_t_warning:
		return "WARNING";
	case msg_t_message:
		return "MESSAGE";
	case msg_t_debug:
		return "DEBUG";
	case msg_t_fatal:
		return "FATAL";
	}
	return "UNKNOWN";
}

#ifdef DEBUG
#warning "DEBUG MODE ACTIVATED\n"

FILE* logger_fd = NULL;

void initDebugLog(const char* dbg_log) {
	logger_fd = fopen(dbg_log, "w");
	if(!logger_fd)
		exitWithError(_errcode_log_error, "Cant open log file.\n");
}

void _logger_write(const char* file, const char* func, unsigned int line, msg_t msgtype, const char* format, ...) {
	va_list val;
	char buffer[2048] = {0};

	va_start(val, format);
	setTColorByMsgType(msgtype);
	snprintf(buffer, " >> %s - %-7s -> %s : %s : %d - %s\n", __TIME__, getMsgStr(msgtype), file, func, line, format);
	vfprintf(stderr, buffer, val);
	setTColorByMsgType(0);
	va_end(val);
}

void closeDebugLog() {
	fclose(logger_fd);
}

#else

void initDebugLog(const char* dbg_log) {
}

void _logger_write(const char* file, const char* func, unsigned int line, msg_t msgtype, const char* format, ...) {

}

void closeDebugLog() {
}

#endif
