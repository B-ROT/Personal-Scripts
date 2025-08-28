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
        printf("Invalid input...\n");
    }
}

void SetMonitorMode () {
    printf("Setting card to monitor mode...\n");

    system("sudo systemctl stop iwd");
    printf("Process iwd stopped...\n");
    
    system("sudo airmon-ng start");
    printf("Monitor interface online...\n");
    
    system("ip link show wlan0mon");
    printf("Monitor mode interface status...\n");
    
    system("iw dev wlan0mon info");
    printf("Monitor mode set...\n");
}

void SetManagedMode() {
    printf("Setting card to managed mode...\n");
    
    system("sudo airmon-ng stop wlan0mon");
    printf("Taking monitor mode interface offline...\n");
    
    system("sudo systemctl start iwd");
    printf("Process iwd started...\n");
    
    sleep(1);
    
    system("ip link show wlan0");
    printf("wlan0 status...\n");
    
    system("iw dev wlan0 info");
    printf("wlan0 mode set to managed...\n");
}
