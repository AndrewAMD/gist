// This would be a simple C interface for a DTC Protocol client library.

// It would have a dedicated thread running in the background. I would design all of these functions to be thread-safe.
// However, it would allow users to optionally supply callback functions - which would **NOT** be thread-safe.
// The idea is simple: The user must explicitly ask for data to get data.
// That is, this library does not push any data.
// But the callbacks can indicate the presence of new data.

// This type of a setup is perfect for triggering timers to interrupt sleep.

// This library allows as many simultaneous connections as desired.  You can track any given connection with a handler.

// This library promotes asynchronous usage by returning immediately unless a block limit is supplied.
// Note that a "block limit" is not to be confused with a "timeout".
// For example, in Zorro, a healthy Broker Plugin will run BrokerProgress() every ~10ms or so in order to keep the menu buttons alive on the GUI.
