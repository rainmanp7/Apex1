// this is the newest version as of July 16th 2023 3:15pm
// this version employs hash and icmp packet check with fixes 
// to the previous version that didn't have real time checking
// this is apex version 2.0 machine reinforced learning
// especially made congestion control.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define MAX_CONGESTION_WINDOW 1000
struct Connection {
double congestion_window;
};
struct HashTable {
struct Connection *connections;
int size;
};
void hash_table_init(struct HashTable *table, int size) {
table->connections = malloc(sizeof(struct Connection) * size);
table->size = size;
}
void hash_table_insert(struct HashTable *table, int key, struct Connection
connection) {
int index = key % table->size;
table->connections[index] = connection;
}
struct Connection *hash_table_lookup(struct HashTable *table, int key) {
int index = key % table->size;
return &table->connections[index];
}
double congestion_control(unsigned long value, size_t packet_size) {
double congestion_window_size = value * 2;
if (congestion_window_size > MAX_CONGESTION_WINDOW) {
congestion_window_size = MAX_CONGESTION_WINDOW;
}
double new_congestion_window = reinforcement_learning_model.predict(
congestion_window_size, packet_size);
enum CongestionType {
NORMAL,
SLOW_START,
CONGESTION_AVOIDANCE,
DISTURBED,
};
CongestionType congestion_type;
switch (congestion_type) {
case NORMAL:
double round_trip_time = get_round_trip_time();
double bandwidth = get_bandwidth();
new_congestion_window = new_congestion_window * (
1 + round_trip_time / 100 + bandwidth / 100000);
break;
case CONGESTION_AVOIDANCE:
new_congestion_window = new_congestion_window / 2 + (
get_number_of_connections() / 100);
break;
case DISTURBED:
double disturbance_severity = get_disturbance_severity();
new_congestion_window = new_congestion_window * (1 -
disturbance_severity);
break;
default:
break;
}
struct Connection *connection = hash_table_lookup(connections, key);
connection->congestion_window = new_congestion_window;
free(connections);
return new_congestion_window;
}
double get_round_trip_time() {
double round_trip_time;
struct icmphdr icmphdr;
icmphdr.type = ICMP_ECHO_REQUEST;
icmphdr.code = 0;
icmphdr.checksum = 0;
icmphdr.id = htons(1234);
icmphdr.seq = htons(1);
int datalen = sizeof(icmphdr);
int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
if (sockfd < 0) {
perror("socket");
exit(1);
}
sendto(sockfd, &icmphdr, datalen, 0, (struct sockaddr *)&servaddr,
sizeof(servaddr));
struct sockaddr_in from;
socklen_t fromlen = sizeof(from);
int recvlen = recvfrom(sockfd, &icmphdr, datalen, 0, (struct sockaddr
*)&from, &fromlen);
if (recvlen < 0) {
perror("recvfrom");
exit(1);
}
round_trip_time = (double)recvlen / 2;
return round_trip_time;
}
double get_bandwidth() {
double bandwidth = 100000;
return bandwidth;
}
double get_disturbance_severity() {
double disturbance_severity = 0.5;
return disturbance_severity;
}
int main() {
double congestion_window_size = 100;
size_t packet_size = 1000;
double new_congestion_window =
congestion_control(congestion_window_size,
packet_size);
printf("The new congestion window size is %f\n", new_congestion_window);
return 0;
}
