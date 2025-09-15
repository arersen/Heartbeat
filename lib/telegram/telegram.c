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

int telegram_send_message(char* token, char* chat_id, char* message) {
#ifdef _WIN32
    wchar_t query[1024] = {0};
    swprintf(query, sizeof(query) / sizeof(query[0]), L"/bot%s/sendMessage?chat_id=%s&text=%s", token, chat_id, message);
    HINTERNET hSession = WinHttpOpen(L"MyApp/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession) return FAILED;

    HINTERNET hConnect = WinHttpConnect(hSession,
                                      L"api.telegram.org",
                                      INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) return FAILED;

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET",
                                            query,
                                            NULL, WINHTTP_NO_REFERER,
                                            WINHTTP_DEFAULT_ACCEPT_TYPES,
                                            WINHTTP_FLAG_SECURE);

    if (!hRequest) return FAILED;

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
#else
    CURL *curl;
    CURLcode res;

    char url[1024];
    snprintf(url, sizeof(url),
             "https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s",
             token, chat_id, message);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);


        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printf("Message sent!\n");

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize curl\n");
        return FAILED;
    }

    curl_global_cleanup();
#endif

    return OK;

}
