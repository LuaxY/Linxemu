#ifndef UTILS_H
#define UTILS_H

#include "hexdump.h"
#include "Logger.h"
#include "MessageReader.h"
#include "MessageWriter.h"

#define positionLog() { cout << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << ":" << __LINE__ << ":" << __FUNCTION__ << "()" << endl; }

#endif // UTILS_H
