// This would be a simple C interface for a DTC Protocol client library.

// It would have a dedicated thread running in the background. I would design all of these functions to be thread-safe.
// However, it would allow users to optionally supply callback functions - which would **NOT** be thread-safe.
// The idea is simple: The user must explicitly ask for data to get data.
// That is, this library does not push any data.
// But the callbacks can indicate the presence of new data.

// This type of a setup is perfect for triggering timers to interrupt sleep.

// This library allows as many simultaneous connections as desired.  You can track any given connection with a handler.
// Also, you can count the number of active connections.
// Most DTC servers will supply one or two ports to cover all functionality.  Sierra Chart's built-in server has two ports.

// This library promotes asynchronous usage by returning immediately unless a block limit is supplied.
// Note that a "block limit" is not to be confused with a "timeout".
// For example, in Zorro, a healthy Broker Plugin will run BrokerProgress() every ~10ms or so in order to keep the menu buttons alive on the GUI.

typedef struct LDTC_CONFIG
{
  char host[32];
  char port[32];
  bool tls_enabled;
  // TO DO
} LDTC_CONFIG;





// immediately returns handler of new connection.
// Connection task is assigned to background thread.
// Returns handler to this new connection.
// LDTC_ID ldtc_new_connection(LDTC_CONFIG* config);

// If not set, there will be one connection.
void dtc_set_number_of_connections(int n_connections);

typedef uint8_t LDTC_ID;  // Socket ID's
// REGARDING SOCKET ID'S:
// The sockets will be numbered from zero thru (n_connections - 1).
// For example, if there are four connections, the ID's will be 0, 1, 2, & 3.



enum LDTC_STATUS
{
  status_not_done = 0,          // Nothing to report at this time.
  status_have_message = 1,      // High priority output! Must read all messages on queue to make this disappear.
  status_satisfied = 2,         // Connection is active, and there is no output to block for.
  status_uninitiated = 11,      // This socket is standing by for launch.
  status_terminated = 12,       // This socket is done operating. To use again, re-launch this socket.
}

// Returns the status of the connection within limit milliseconds.
// If the limit is zero, the status returns immediately.
LDTC_STATUS ldtc_status(LDTC_HANDLE h, int limit_ms);

#define LDTC_MESSAGE_LENGTH 256

// Writes a message to the supplied char array of size LDTC_MESSAGE_LENGTH.
// This will pop the first message from the front of the message queue.
// Returns the number of messages remaining on the queue, or -1 if there was an error.
// Optionally, user will supply pointer to int alert_level: output level of alert required:
//  1: Log only
//  2: Print to screen
//  3: Pop up dialog
// alert_level will be ignored if user supplies a NULL pointer.
int ldtc_message(LDTC_HANDLE h, char* msg_output, int* alert_level);


