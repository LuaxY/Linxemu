#ifndef MESSAGES_LIST_H
#define MESSAGES_LIST_H

#include "handshake/ProtocolRequired.h" // 1
#include "connection/HelloConnectMessage.h" // 3
#include "connection/IdentificationMessage.h" // 4
#include "connection/IdentificationFailedMessage.h" // 20
#include "connection/IdentificationSuccessMessage.h" // 22
#include "connection/ServersListMessage.h" // 30
#include "connection/ServerSelectionMessage.h" // 40
#include "connection/SelectedServerRefusedMessage.h" // 41
#include "connection/SelectedServerDataMessage.h" // 42
#include "common/basic/BasicPingMessage.h" // 182
#include "common/basic/BasicPongMessage.h" // 183
#include "connection/ClearIdentificationMessage.h" // 888
#include "security/RawDataMessage.h" // 6253

#endif // MESSAGES_LIST_H
