#include "listen.h"
#include "logger.h"
#include "bot.h"

#include <windows.h>

extern Bot_State bot;

void listen_to_master() {
    HANDLE pipe = CreateFile("\\\\.\\pipe\\lazy_commands", GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);
	if (!pipe) {
        return;
	}

	u32 bytes_read;
	char event[1024];
	while (ReadFile(pipe, event, sizeof(event)-1, &bytes_read, NULL)) {
        Event_Type ev = event[0];
        // I could probably use a table of function pointers instead of this ugly switch
        switch (ev) {
        case evStart:
            bot.running = true;
        case evListEntities:
            LINFO("Populate entity list and send info to master");
        }
    }

	CloseHandle(pipe);
}