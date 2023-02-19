#include "listen.h"
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
	char command[1024];
	while (ReadFile(pipe, command, sizeof(command)-1, &bytes_read, NULL)) {
        Operation_Type op = command[0];
        switch (op) {
        case opStart:
            bot.running = true;
        }
    }

	CloseHandle(pipe);
}