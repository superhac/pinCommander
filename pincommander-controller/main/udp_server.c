/*
 * PinCommander - Controller
 *
 * Author: Superhac
 *
 *  Generic Public Domain - AKA do whatever you want!
 */

#include "udp_server.h"
#include "keymaps.h"
#include "usb.h"

#define PORT 9797

/* Message ID */
#define MSG_ID_HMI_BUTTON_PRESS 1
#define MSG_ID_CAB_TEMP 2
#define MSG_ID_PONG_RESP 3
#define MSG_ID_PING_REQ 4

static const char *TAG = "udp_server.c";

void process_hmi_button(char *msgData)
{

    // int test = strcmp(msgData, "PINVOL_GLOBAL_VOL_UP_KEYMAP");
    // ESP_LOGI(TAG, " '%s' compare: %d msgdata: %d literial:%d  ", msgData, test, strlen(msgData), strlen("PINVOL_GLOBAL_VOL_UP_KEYMAP"));

    if (strcmp(msgData, "PINVOL_GLOBAL_VOL_UP_KEYMAP") == 0)
    {
        ESP_LOGI(TAG, "match!");
        send_hid_keyboard(PINVOL_GLOBAL_VOL_UP_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_GLOBAL_VOL_DOWN_KEYMAP") == 0)
    {
        send_hid_keyboard(PINVOL_GLOBAL_VOL_DOWN_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_GLOBAL_NIGHT_MODE_KEYMAP") == 0)
    {
        send_hid_keyboard(PINVOL_GLOBAL_NIGHT_MODE_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_GLOBAL_MUTE_KEYMAP") == 0)
    {
        send_hid_keyboard(PINVOL_GLOBAL_MUTE_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_TABLE_VOL_UP_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_TABLE_VOL_UP_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_TABLE_VOL_DOWN_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_TABLE_VOL_DOWN_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_SSF_BG_VOL_UP_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_SSF_BG_VOL_UP_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_SSF_BG_VOL_DOWN_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_SSF_BG_VOL_DOWN_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_SSF_REAR_VOL_UP_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_SSF_REAR_VOL_UP_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_SSF_REAR_VOL_DOWN_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_SSF_REAR_VOL_DOWN_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_SSF_FRONT_VOL_UP_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_SSF_FRONT_VOL_UP_KEYMAP);
    }
    else if (strcmp(msgData, "PINVOL_SSF_FRONT_VOL_DOWN_KEYMAP") == 0)
    {
        send_hid_consumer(PINVOL_SSF_FRONT_VOL_DOWN_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_EBBUYIN_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_EBBUYIN_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_COIN3_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_COIN3_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_COIN4_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_COIN4_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_DOOR_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_DOOR_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_CANCEL_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_CANCEL_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_DOWN_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_DOWN_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_UP_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_UP_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_ENTER_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_ENTER_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_SHOWOPTS_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_SHOWOPTS_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_SHOWKEYS_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_SHOWKEYS_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_RESETEMU_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_RESETEMU_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_DIP_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_DIP_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_WINDOWLOCK_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_WINDOWLOCK_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_ADDEBALL_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_ADDEBALL_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_DISPLAYSIZE_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_DISPLAYSIZE_KEYMAP);
    }
    else if (strcmp(msgData, "PINMAME_BANGBACK_KEYMAP") == 0)
    {
        send_hid_keyboard(PINMAME_BANGBACK_KEYMAP);
    }

    else
    {
        ESP_LOGI(TAG, "unknown button: %s", msgData);
    }
}

void send_ping_resp()
{
    ESP_LOGI(TAG, "Sending Pong Reply");
    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(9797);
    int addr_family = AF_INET;
    int ip_protocol = IPPROTO_IP;

    int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
    int err = sendto(sock, "controller/3/pong", strlen("controller/3/pong") - 1, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)); // -1 to remove null
}

static void process_msg(char *addr_str, char *rx_buffer, int len)
{
    ESP_LOGI(TAG, "Parse udp msg");
    char *msgSenderID = NULL;
    char *msgID = NULL;
    char *msgData = NULL;

    char *tokenStore;
    tokenStore = strtok(rx_buffer, "/");
    if (tokenStore != NULL)
    {
        msgSenderID = strdup(tokenStore);
    }
    tokenStore = strtok(NULL, "/");
    if (tokenStore != NULL)
    {
        msgID = strdup(tokenStore);
    }
    tokenStore = strtok(NULL, "/");
    if (tokenStore != NULL)
    {
        // ESP_LOGI(TAG, "----- token=%s len=%d", tokenStore, strlen(tokenStore));
        msgData = strdup(tokenStore);
    }
    // ESP_LOGI(TAG,"%s",msgSenderID);
    // ESP_LOGI(TAG,"%s",msgID);

    if (msgData != NULL)
    {
        ESP_LOGI(TAG, "%s", msgData);
    }

    if (msgID != NULL)
    {
        switch (atoi(msgID))
        {
        case 0:
            ESP_LOGI(TAG, "invalid msgID? atoi reutned 0");
            break;
        case MSG_ID_HMI_BUTTON_PRESS:
            if (msgSenderID != NULL && msgData != NULL)
            {
                ESP_LOGI(TAG, "Recv HMI button press");
                ESP_LOGI(TAG, "%s", msgData);
                process_hmi_button(msgData);
            }
            break;
        case MSG_ID_PING_REQ:
            send_ping_resp();
            break;
        default:
            ESP_LOGI(TAG, "could not match msgID?");
            break;
        }
    }
    else
    {
        ESP_LOGI(TAG, "unknown packet=");
        ESP_LOGI(TAG, "%s", rx_buffer);
    }

    free(msgSenderID);
    free(msgID);
    free(msgData);
}

extern void udp_server_task(void *pvParameters)
{
    char rx_buffer[128];
    char addr_str[128];
    int addr_family = (int)pvParameters;
    int ip_protocol = 0;
    struct sockaddr_in6 dest_addr;

    while (1)
    {

        if (addr_family == AF_INET)
        {
            struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
            dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
            dest_addr_ip4->sin_family = AF_INET;
            dest_addr_ip4->sin_port = htons(PORT);
            ip_protocol = IPPROTO_IP;
        }
        else if (addr_family == AF_INET6)
        {
            bzero(&dest_addr.sin6_addr.un, sizeof(dest_addr.sin6_addr.un));
            dest_addr.sin6_family = AF_INET6;
            dest_addr.sin6_port = htons(PORT);
            ip_protocol = IPPROTO_IPV6;
        }

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0)
        {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created");

#if defined(CONFIG_LWIP_NETBUF_RECVINFO) && !defined(CONFIG_EXAMPLE_IPV6)
        int enable = 1;
        lwip_setsockopt(sock, IPPROTO_IP, IP_PKTINFO, &enable, sizeof(enable));
#endif

#if defined(CONFIG_EXAMPLE_IPV4) && defined(CONFIG_EXAMPLE_IPV6)
        if (addr_family == AF_INET6)
        {
            // Note that by default IPV6 binds to both protocols, it is must be disabled
            // if both protocols used at the same time (used in CI)
            int opt = 1;
            setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &opt, sizeof(opt));
        }
#endif
        // Set timeout
        struct timeval timeout;
        timeout.tv_sec = 0; // set 0 for full blocking.
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

        int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err < 0)
        {
            ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        }
        ESP_LOGI(TAG, "Socket bound, port %d", PORT);

        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t socklen = sizeof(source_addr);

#if defined(CONFIG_LWIP_NETBUF_RECVINFO) && !defined(CONFIG_EXAMPLE_IPV6)
        struct iovec iov;
        struct msghdr msg;
        struct cmsghdr *cmsgtmp;
        u8_t cmsg_buf[CMSG_SPACE(sizeof(struct in_pktinfo))];

        iov.iov_base = rx_buffer;
        iov.iov_len = sizeof(rx_buffer);
        msg.msg_control = cmsg_buf;
        msg.msg_controllen = sizeof(cmsg_buf);
        msg.msg_flags = 0;
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_name = (struct sockaddr *)&source_addr;
        msg.msg_namelen = socklen;
#endif

        while (1)
        {
            ESP_LOGI(TAG, "Waiting for data");
#if defined(CONFIG_LWIP_NETBUF_RECVINFO) && !defined(CONFIG_EXAMPLE_IPV6)
            int len = recvmsg(sock, &msg, 0);
#else
            int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);
#endif
            // Error occurred during receiving
            if (len < 0)
            {
                ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
                break;
            }
            // Data received
            else
            {
                // Get the sender's ip address as string
                if (source_addr.ss_family == PF_INET)
                {
                    inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
#if defined(CONFIG_LWIP_NETBUF_RECVINFO) && !defined(CONFIG_EXAMPLE_IPV6)
                    for (cmsgtmp = CMSG_FIRSTHDR(&msg); cmsgtmp != NULL; cmsgtmp = CMSG_NXTHDR(&msg, cmsgtmp))
                    {
                        if (cmsgtmp->cmsg_level == IPPROTO_IP && cmsgtmp->cmsg_type == IP_PKTINFO)
                        {
                            struct in_pktinfo *pktinfo;
                            pktinfo = (struct in_pktinfo *)CMSG_DATA(cmsgtmp);
                            ESP_LOGI(TAG, "dest ip: %s", inet_ntoa(pktinfo->ipi_addr));
                        }
                    }
#endif
                }
                else if (source_addr.ss_family == PF_INET6)
                {
                    inet6_ntoa_r(((struct sockaddr_in6 *)&source_addr)->sin6_addr, addr_str, sizeof(addr_str) - 1);
                }

                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string...
                ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
                ESP_LOGI(TAG, "%s", rx_buffer);
                process_msg(addr_str, rx_buffer, len);

                int err = sendto(sock, rx_buffer, len, 0, (struct sockaddr *)&source_addr, sizeof(source_addr));
                if (err < 0)
                {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }
            }
        }

        if (sock != -1)
        {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}