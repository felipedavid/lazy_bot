auto s_consoleActive         = (b32*) 0x00CABCC4;
auto s_consoleOpen           = (b32*) 0x00CA1978;
auto s_consoleSize           = (f32*) 0x00CA19B0; // 0.0 .. 1.0
auto s_playerName            = (const char *) 0x00C79D18; 
auto s_currentTargetGUID     = (u64*) 0x00BD07B0;
auto s_lastTargetGUID        = (u64*) 0x00BD07B8;
auto s_isLoadingOrConnecting = (b32*) 0x00B6AA38;
auto s_lastHardwareAction    = (u32*) 0x00B499A4;