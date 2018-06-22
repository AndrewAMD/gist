# libdtc ideas

## Unblock on Arrival of Data

Set a timer that expires at LIMIT_MS.

Receive function can trip the timer.  Upon which, the condition is checked again.

On receive, set to MINIMUM TIMEPOINT

std::deque of blocking conditions?

Or just the most recent blocking condition??
