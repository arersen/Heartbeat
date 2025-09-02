//
// Created by gawlik on 02.09.2025.
//

#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
uint8_t write_token(char* token);
uint8_t get_token(char* token);
int telegram_send_message(char* token, char* chat_id, char* message);
#endif //TELEGRAM_H
