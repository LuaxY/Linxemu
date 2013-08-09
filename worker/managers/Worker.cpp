#include "Worker.h"
#include <fstream>

pthread_t Worker::threadPtr = 0;
queue<Message*> Worker::messagesQueue = queue<Message*>();
pthread_mutex_t Worker::mutex_stock = PTHREAD_MUTEX_INITIALIZER;
MessageReceiver Worker::rawParser = MessageReceiver();

Worker::Worker()
{
    pthread_create(&threadPtr, NULL, &Worker::handler, this);
}

void* Worker::handler(void *ptr)
{
    Logger::Log(INFO, sLog(), "Thread Worker started successfully", true);

    rawParser.Register();
    Worker *worker = (Worker*)&ptr;

    int i = 1;

    while(true)
    {
        if(!messagesQueue.empty())
        {
            /*Logger::Log(WORKER, sLog(), "Messsages queue: ", true, false);
            cout << i << endl;*/

            pthread_mutex_lock(&mutex_stock);
                Message *message = messagesQueue.front();
                messagesQueue.pop();
            pthread_mutex_unlock(&mutex_stock);

            /** Pakcet parser **/
            INetworkMessage *netMessage;
            netMessage = rawParser.parse(message->packet);

            if(!netMessage)
            {
                Logger::Log(ERROR, sLog(), "Unknown packet ID: ", false);
                cout << message->packet->messageId << endl;
            }
            else
            {
                Logger::Log(DEBUG, sLog(), "[RCV] ", false);
                cout << netMessage->getMessageName() << " (" << netMessage->getMessageId() << "), " << message->messageLength << " bytes from " << NetworkManager::getClientIP(message->client.sock) << ":" << NetworkManager::getClientPort(message->client.sock) << endl;

                /** Frames dispatcher **/

                //Frames.processMessage(netMessage);

                MessageWriter *data = new MessageWriter();
                MessageWriter *packet = new MessageWriter();

                switch(netMessage->getMessageId())
                {
                    case 4: // IdentificationMessage
                    {
                        ifstream::pos_type size;
                        char *newPacket;

                        // Merci à Munrek pour le SWF
                        ifstream packetSWF("DofusAuthentificator.swf", ios::in | ios::binary | ios::ate);
                        if(packetSWF.is_open())
                        {
                            size = packetSWF.tellg();
                            newPacket = new char[size];
                            packetSWF.seekg(0, ios::beg);
                            packetSWF.read(newPacket, size);
                            packetSWF.close();
                        }
                        else
                            Logger::Log(ERROR, sLog(), "Unable to open DofusAuthentificator.swf");

                        RawDataMessage rdm;
                        rdm.initRawDataMessage(newPacket, size);
                        rdm.pack(data);

                        NetworkManager::writePacket(packet, rdm.getMessageId(), data->getBuffer(), data->getPosition());
                        NetworkManager::sendTo(message->client.sock, packet->getBuffer(), packet->getPosition(), rdm.getInstance());
                        break;
                    }

                    case 182: // BasicPingMessage
                    {
                        BasicPongMessage bpm;
                        bpm.initBasicPongMessage(true);
                        bpm.pack(data);

                        NetworkManager::writePacket(packet, bpm.getMessageId(), data->getBuffer(), data->getPosition());
                        NetworkManager::sendTo(message->client.sock, packet->getBuffer(), packet->getPosition(), bpm.getInstance());
                        break;
                    }

                    case 888: // ClearIdentificationMessage
                    {
                        ClearIdentificationMessage cim((ClearIdentificationMessage*)netMessage);
                        cout << "User: " << cim.user << " Password: " << cim.password << endl;
                        break;
                    }
                }

                delete data;
                delete packet;
            }

            /** Delete packet **/
            worker->removeMessage(netMessage, message);

            i++;
        }

        usleep(30*1000);
    }
}

bool Worker::addMessage(Client client, unsigned short messageId, unsigned short messageLength, Packet* packet)
{
    Message *message = new Message;

    message->client = client;
    message->messageId = messageId;
    message->messageLength = messageLength;
    message->packet = packet;

    pthread_mutex_lock(&mutex_stock);
        messagesQueue.push(message);
    pthread_mutex_unlock(&mutex_stock);

    return true;
}

void Worker::removeMessage(INetworkMessage* netMessage, Message* message)
{
    delete netMessage;
    delete message->packet;
    delete message;
}

void Worker::clearMessagesQueue()
{
    while(!messagesQueue.empty())
    {
        pthread_mutex_lock(&mutex_stock);
            Message *message = messagesQueue.front();
            messagesQueue.pop();
        pthread_mutex_unlock(&mutex_stock);

        delete message->packet;
        delete message;
    }
}
