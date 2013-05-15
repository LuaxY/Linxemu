#include "Worker.h"

int Worker::m_global = 0;
pthread_t Worker::threadPtr = 0;

Worker::Worker()
{
    int ret = pthread_create(&threadPtr, NULL, &Worker::thread, this);
}

void* Worker::thread(void *ptr)
{
    Logger::Log(INFO, "Thread Worker started successfully");

    while(true)
    {
        Logger::Log(ERROR, "[THREAD] global: ", false);
        cout << m_global << endl;
        usleep(30*1000);
    }
}

void Worker::run()
{
    while(true)
    {
        m_global++;
        sleep(2);
    }
}
