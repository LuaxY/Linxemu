#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>
#include <unistd.h>
#include <iostream>

#include "../../utils/utils.h"

using namespace std;

class Worker
{
    public:
        Worker();
        void run();

    private:
        static void* thread(void *ptr);
        static pthread_t threadPtr;
        static int m_global;
};

#endif // WORKER_H
