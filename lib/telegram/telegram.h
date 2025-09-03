//
// Created by gawlik on 02.09.2025.
//

#ifndef TELEGRAM_H
#define TELEGRAM_H


#include <stdio.h>
#include <stdint.h>
#include <wchar.h>

#ifdef _WIN32
#include <windows.h>
#include <winhttp.h>\
#else
#include <curl/curl.h>
#endif


int write_token(char* token);
int get_token(char* token);
int telegram_send_message(char* token, char* chat_id, char* message);
#endif //TELEGRAM_H
