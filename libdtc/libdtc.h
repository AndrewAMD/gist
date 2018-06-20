// This would be a simple C interface for a DTC Protocol client library.

// It would have a dedicated thread running in the background. I would design all of these functions to be thread-safe.
// It would also allow users to optionally supply callback functions.  But it **never** pushes data to the callbacks.

// The idea is simple: The user must explicitly ask for data to get data.
// The callbacks simply indicate the presence of new data.

// This library allows as many simultaneous socket connections as desired.
// You can track a socket by a socket ID.  You can launch, terminate, and re-launch any given socket.
// Most DTC servers will supply one or two ports to cover all functionality.  Sierra Chart's built-in server has two ports.

// This library promotes asynchronous usage by returning immediately unless a block limit is supplied.
// Note that a "block limit" is not to be confused with a "timeout".
// For example, in Zorro, a healthy Broker Plugin will run BrokerProgress() every ~10ms or so in order 
//    to keep the menu buttons alive on the GUI.
// In that case, the command will unblock the very instant it receives the required response - or 10ms, whichever comes first.
// Optionally, you can block synchronously until a required response is received.  
//    This approach is **not** recommended, because your program will be entirely stalled until satisfaction (or timeout).

// Various functions return what is called a "response handle".
// You can track if and when a response to a certain message has been received.
typedef uint64_t RESPONSE_HANDLE;

typedef struct LDTC_CONFIG
{
  char host[32];
  char port[32];
  bool tls_enabled;
  // TO DO
} LDTC_CONFIG;

// Sets the number of sockets.  (If not set, the default is 1).
// Returns true if command accepted - false if rejected.
// If not set, there will be one connection.
// If the number of sockets is decreasing, the disappearing sockets will be terminated first.
bool dtc_set_num_sockets(int num_sockets);

typedef uint8_t LDTC_ID;  // Socket ID's
// REGARDING SOCKET ID'S:
// The sockets will be numbered from zero thru (n_connections - 1).
// For example, if there are four connections, the ID's will be 0, 1, 2, & 3.

// launches the given socket with the given configuration.
// If this is the first launch, a new thread will be created - it will stay open for the duration of the program,
//     even if all sockets are closed.
// For any launch after that, the communications tasks will simply be added to the same background thread.
// This thread will continuously operate asynchronously.
// If open, the socket will be closed and re-launched with the new configuration.
// Returns if command accepted, false if command rejected.
bool dtc_launch(LDTC_ID id, const LDTC_CONFIG* config);

enum LDTC_STATUS
{
  status_satisfied = 0,         // Connection is active, and there is no output to block for.
  status_unsatisfied = 1,       // Awaited response not yet received.  Check status again.
  status_unread_messages = 2,   // One or more messages are ready to be printed/logged. Must read to get other status codes. 
  status_uninitiated = 11,      // This socket is standing by for launch.
  status_terminated = 12        // This socket is done operating. To use again, re-launch this socket.
};

// Returns the status of the connection within limit milliseconds.
// If the limit is zero, the status returns immediately.
// To check whether or not a certain response was received, supply a RESPONSE_HANDLE
//    returned from one of the other functions.
//    Otherwise, set h to NULL.
// If the response was received, returns status_satisfied.
// If the response was not yet received after limit_ms milliseconds, returns status_satisfied.
LDTC_STATUS ldtc_status(LDTC_ID id, RESPONSE_HANDLE h, int limit_ms);

#define LDTC_MESSAGE_LENGTH 256

// Writes a message to the supplied char array of size LDTC_MESSAGE_LENGTH.
// This will pop the first message from the front of the message queue.
// Returns the number of messages remaining on the queue, or -1 if there was an error.
// Optionally, user will supply pointer to int alert_level: output level of alert required:
//  1: Log only
//  2: Print to screen
//  3: Pop up dialog
// alert_level will be ignored if user supplies a NULL pointer.
int ldtc_message(LDTC_ID id, char* msg_output, int* alert_level);


