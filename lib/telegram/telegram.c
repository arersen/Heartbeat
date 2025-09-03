//
// Created by gawlik on 02.09.2025.
//

#include "telegram.h"

int write_token(char* token) {
    FILE* fp = fopen("token.txt", "w");
    if (!fp) {
        return 0;
    }
    fputs(token, fp);
    fclose(fp);
    return 0;
}

int get_token(char* token) {
    FILE* fp = fopen("token.txt", "r");
    if (!fp) {
        return 0;
    }
    fgets(token, 256, fp);
    return 0;

}
#ifdef _WIN32
int telegram_send_message(char* token, char* chat_id, char* message) {
    wchar_t query[1024] = {0};
    swprintf(query, sizeof(query) / sizeof(query[0]), L"/bot%s/sendMessage?chat_id=%s&text=%s", token, chat_id, message);
    HINTERNET hSession = WinHttpOpen(L"MyApp/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession) return 1;

    HINTERNET hConnect = WinHttpConnect(hSession,
                                      L"api.telegram.org",
                                      INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) return 1;

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET",
                                            query,
                                            NULL, WINHTTP_NO_REFERER,
                                            WINHTTP_DEFAULT_ACCEPT_TYPES,
                                            WINHTTP_FLAG_SECURE);

    if (!hRequest) return 1;

    BOOL bResults = WinHttpSendRequest(hRequest,
                                       WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                                       WINHTTP_NO_REQUEST_DATA, 0,
                                       0, 0);

    if (bResults) bResults = WinHttpReceiveResponse(hRequest, NULL);

    if (bResults)
        printf("Message sent!\n");
    else
        printf("Error sending message.\n");

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 0;

}
#else
int telegram_send_message(char* token, char* chat_id, char* message) {

}
#endif
