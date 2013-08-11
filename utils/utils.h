#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include "hexdump.h"
#include "Logger.h"
#include "MessageReader.h"
#include "MessageWriter.h"
#include "BooleanByteWrapper.h"

#define pLog() { cout << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << ":" << __LINE__ << ":" << __FUNCTION__ << "()" << endl; }
#define sLog() ({ stringstream ret; ret << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << ":" << __LINE__ << ":" << __FUNCTION__ << "()"; ret.str(); })

#endif // UTILS_H
