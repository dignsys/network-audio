#ifndef __network_audio_H__
#define __network_audio_H__

#include <dlog.h>

#if !defined(PACKAGE)
#define PACKAGE "org.example.network_audio"
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "network_audio"

#define ERR(fmt, args...) dlog_print(DLOG_ERROR, LOG_TAG, "%s : %s(%d) > "fmt"\n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define WARN(fmt, args...) dlog_print(DLOG_WARN, LOG_TAG, "%s : %s(%d) > "fmt"\n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define INFO(fmt, args...)  dlog_print(DLOG_INFO, LOG_TAG, "%s : %s(%d) > "fmt"\n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)
#define DBG(fmt, args...) dlog_print(DLOG_DEBUG, LOG_TAG, "%s : %s(%d) > "fmt"\n", rindex(__FILE__, '/') + 1, __func__, __LINE__, ##args)

#define FN_CALL dlog_print(DLOG_DEBUG, LOG_TAG, "%s : %s(%d) >>>>>>>> called", rindex(__FILE__, '/') + 1, __func__, __LINE__)
#define FN_END dlog_print(DLOG_DEBUG, LOG_TAG, "%s : %s(%d) <<<<<<<< ended", rindex(__FILE__, '/') + 1, __func__, __LINE__)

#endif /* __network_audio_H__ */
