#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
void SetMonitorMode();
void SetManagedMode();

int main () {
    int m;
    printf("Do you want to set the net card to:\n\n[1]Monitor-mode\t[2]Managed-mode\n\nSet(1/2): ");
    scanf("%d",&m);

    if (m == 1) {
        SetMonitorMode();
    } 
    
    else if (m == 2) {
        SetManagedMode();
    }
    else {
        printf("\033[0;31mInvalid input...\033[0m\n");
    }
}

void SetMonitorMode () {
    printf("\033[0;32mSetting card to monitor mode...\033[0m\n");

    printf("\033[0;32mProcess iwd stopped...\033[0m\n");
    system("sudo systemctl stop iwd");
    system("systemctl status iwd | grep --color=always Active");
    
    printf("\033[0;32mMonitor interface online...\033[0m\n");
    system("yes | head -n 1 | sudo airmon-ng start 2> /dev/null");
    
    printf("\033[0;32mMAC address of the monitor interface changed...\033[0m\n");
    system("sudo ip link set wlan0mon down"); 
    system("sudo macchanger --random --bia wlan0mon");
    system("sudo ip link set wlan0mon up");

    printf("\033[0;32mMonitor mode interface status...\033[0m\n");
    system("ip link show wlan0mon");
    
    printf("\033[0;32mMonitor mode set...\033[0m\n");
    system("iw dev wlan0mon info | grep --color=always type");
}

void SetManagedMode() {
    printf("\033[0;32mSetting card to managed mode...\033[0m\n");
    
    printf("\033[0;32mTaking monitor mode interface offline...\033[0m\n");
    system("sudo airmon-ng stop wlan0mon");
    
    printf("\033[0;32mProcess iwd started...\033[0m\n");
    system("sudo systemctl start iwd");
    system("systemctl status iwd | grep --color=always Active");
    
    sleep(1);
    
    printf("\033[0;32mwlan0 status...\033[0m\n");
    system("ip link show wlan0");
    
    printf("\033[0;32mwlan0 mode set to managed...\033[0m\n");
    system("iw dev wlan0 info | grep --color=always type");
}
