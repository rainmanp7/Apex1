// This is my apex22 network control that will be used
// in conjunction with the reinforcement congestion control

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>
#include <time.h>
#include <omp.h>
const char *settings[] = {
"net.core.somaxconn",
"net.ipv4.tcp_abort_on_overflow",
"net.ipv4.tcp_max_orphans",
"net.ipv4.tcp_max_syn_backlog",
"net.core.netdev_max_backlog",
"net.ipv4.tcp_fastopen",
"net.ipv4.tcp_tw_reuse",
"net.ipv4.tcp_tw_recycle",
"net.ipv4.tcp_slow_start_after_idle",
"net.ipv4.udp_rmem_min",
"net.ipv4.udp_wmem_min",
"net.ipv4.tcp_max_tw_buckets",
"net.ipv4.tcp_mem"
};
int settings_array[sizeof(settings) / sizeof(settings[0])];
int main() {
// Read the settings from the configuration file.
FILE *file = fopen("/etc/sysctl.conf", "r");
if (file == NULL) {
fprintf(stderr, "Error: Could not open configuration file\n");
return -1;
}
char line[1024];
while (fgets(line, sizeof(line), file) != NULL) {
// Split the line into words.
char *words[10];
int i = 0;
while (line[i] != '\0' && i < sizeof(words) / sizeof(words[0])) {
if (line[i] == ' ') {
line[i] = '\0';
} else {
words[i++] = &line[i];
}
i++;
}
// Find the setting that we are looking for.
for (int i = 0; i < sizeof(settings) / sizeof(settings[0]); i++) {
if (strcmp(words[0], settings[i]) == 0) {
// Get the value of the setting.
int value = atoi(words[1]);
settings_array[i] = value;
}
}
}
fclose(file);
// Write the settings to the configuration file.
file = fopen("/etc/sysctl.conf", "w");
if (file == NULL) {
fprintf(stderr, "Error: Could not open configuration file\n");
return -1;
}
for (int i = 0; i < sizeof(settings) / sizeof(settings[0]); i++) {
// Check if the setting is valid.
if (settings_array[i] < 0) {
fprintf(stderr, "Error: Invalid setting %s\n", settings[i]);
return -1;
}
// Write the setting to the configuration file.
fprintf(file, "%s = %d\n", settings[i], settings_array[i]);
}
fclose(file);
return 0;
}
