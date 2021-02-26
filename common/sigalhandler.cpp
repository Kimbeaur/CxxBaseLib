#include <map>
#include <signal.h>
#include "sigalhandler.h"

namespace {
    std::map<int, SignalFuncPtr> handlers;
    void signal_handler(int sig) {
        handlers[sig]();
    }
}
void Signal::signal(int sig, const SignalFuncPtr& handler) {
    handlers[sig] = handler;
    ::signal(sig, signal_handler);
}
// end of local file.