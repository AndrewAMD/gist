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

typedef struct DTC_CONNECTION_CONFIG
{
  char host[32];
  char port[32];
  bool tls_enabled;
  // TO DO
} DTC_CONNECTION_CONFIG;

// immediately returns handler of new connection.
// Connection task is assigned to background thread.
// Returns handler to this new connection.
uint32_t new_connection(DTC_CONNECTION_CONFIG* config);

enum DTC_CONNECTION_STATUS
{
  status_please_wait = 0,
  status_connection_failed =1,
  status_handshake_failed = 2,
  status_login_failed = 3,
  status_login_successful = 4,
  // TO DO
}

// immediately returns the status of the connection.
DTC_CONNECTION_STATUS check_connection(uint32_t handler);
