#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>		/* for NF_ACCEPT */
#include <errno.h>
#include "stc.h"
#include <arpa/inet.h>
#include<string.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>        // close()
#include <chrono>
#include <vector>
#define START_TIME auto s = std::chrono::high_resolution_clock::now();
#define END_TIME auto ed = std::chrono::high_resolution_clock::now();\
    std::chrono::duration<double> diff = ed - s;\
    std::cout << diff.count() << " seconds." << std::endl;
int on = 1;
std::unordered_set<std::string> site;
void dump(unsigned char* buf, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (i != 0 && i % 16 == 0)
			printf("\n");
		printf("%02X ", buf[i]);
	}
	printf("\n");
}
int idxx=0;
int e;
/* returns packet id */
static u_int32_t print_pkt (struct nfq_data *tb)
{
	int id = 0;
	struct nfqnl_msg_packet_hdr *ph;
	struct nfqnl_msg_packet_hw *hwph;
	u_int32_t mark,ifi;
	int ret;
	unsigned char *data;
	int size;
	ph = nfq_get_msg_packet_hdr(tb);
	if (ph) {
		id = ntohl(ph->packet_id);
		printf("hw_protocol=0x%04x hook=%u id=%u ",
			ntohs(ph->hw_protocol), ph->hook, id);
	}

	hwph = nfq_get_packet_hw(tb);
	if (hwph) {
		int i, hlen = ntohs(hwph->hw_addrlen);

		printf("hw_src_addr=");
		for (i = 0; i < hlen-1; i++)
			printf("%02x:", hwph->hw_addr[i]);
		printf("%02x ", hwph->hw_addr[hlen-1]);
	}

	mark = nfq_get_nfmark(tb);
	if (mark)
		printf("mark=%u ", mark);

	ifi = nfq_get_indev(tb);
	if (ifi)
		printf("indev=%u ", ifi);

	ifi = nfq_get_outdev(tb);
	if (ifi)
		printf("outdev=%u ", ifi);
	ifi = nfq_get_physindev(tb);
	if (ifi)
		printf("physindev=%u ", ifi);

	ifi = nfq_get_physoutdev(tb);
	if (ifi)
		printf("physoutdev=%u ", ifi);

	ret = nfq_get_payload(tb, &data);
	if (ret >= 0){
		printf("payload_len=%d\n", ret);
		struct libnet_ipv4_hdr * ipv4 = (struct libnet_ipv4_hdr *)data;
		printf("IP src = %s\n",inet_ntoa(ipv4->ip_src));
		printf("IP dst = %s\n",inet_ntoa(ipv4->ip_dst));
		if (ipv4->ip_p==6){
			struct libnet_tcp_hdr * tcp = (struct libnet_tcp_hdr *)((char *)ipv4+(ipv4->ip_hl<<2));
			printf("TCP src = %d\n",ntohs(tcp->th_sport));
			printf("TCP dst = %d\n",ntohs(tcp->th_dport));
			if(ntohs(tcp->th_dport)==80){
				char * http=(char *)tcp+(tcp->th_off<<2);
				printf("total = %d, ip = %d, tcp = %d \n",ntohs(ipv4->ip_len),ipv4->ip_hl<<2, tcp->th_off<<2);
				int http_len;
				http_len = ntohs(*(int16_t *)((char *)ipv4+2)) - (ipv4->ip_hl<<2) - (tcp->th_off<<2);	
				
				
				printf("http_len = %d\n",http_len);
				http[http_len]='\x00';
				std::string httpStr((char *)http);
				
				if((!memcmp(http, "GET",3 ) || !memcmp(http, "POST",4))&&http_len!=0 ){
					char * name = strstr(http, "Host: ");
					printf("HTTP\n");
					dump((unsigned char *)tcp+(tcp->th_off<<2),http_len);
					std::cout<<httpStr<<"\n";
					if (name) {
						size=site.size();
						name = strtok(name + 6, "\r\n");
						std::string nameStr((char *)name);
						std::cout<<name<<"\n";
						START_TIME
						if(site.find(nameStr)!=site.end()){
							END_TIME
							on=0;
							
							std::cout<<name<<"is not allowed.\n";

						}
						else{
							std::cout<<"OK\n";
							END_TIME
						}
					}
				}
				else if(!memcmp(http, "HTTP",4)){
					dump((unsigned char *)tcp+(tcp->th_off<<2),http_len);
				}
			}

		}

		
	}
	        

	fputc('\n', stdout);

	return id;
}


static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
	      struct nfq_data *nfa, void *data)
{
	u_int32_t id = print_pkt(nfa);
	printf("entering callback\n");
	if (on) return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
	else{
		on=1;
		return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);
		
	}

}

int main(int argc, char **argv)
{
	if (argc != 2) {
        	printf("Usage: sudo %s [filename]\n", argv[0]);
        	return 1;
	}
	struct nfq_handle *h;
	struct nfq_q_handle *qh;
	struct nfnl_handle *nh;
	int fd;
	int rv;
	std::vector<std::string> v;
	int f = open(argv[1],O_RDONLY);
        if (f == -1) {
            std::cerr << "can not open" << "\n";
            return 1;
        }


    char buffer[1000];
    int size;
	std::string left;
	START_TIME
    while ((size = read(f, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[size] = '\0';
        std::string str = left + std::string(buffer);
        unsigned long long int start = 0, end;
        while ((end = str.find('\n', start)) != std::string::npos) {
            std::string s = str.substr(start, end - start);
            unsigned long long int Pos = s.find(',');
            if (Pos != std::string::npos) {
                site.insert(s.substr(Pos + 1));
            }
            start = end + 1;
        }
        left = str.substr(start);
    }
    if (!left.empty()) {
        unsigned long long int Pos = left.find(',');
        if (Pos != std::string::npos) {
            site.insert(left.substr(Pos + 1));
        }
    }

    close(f);
    END_TIME

	


	char buf[4096] __attribute__ ((aligned));

	printf("opening library handle\n");
	h = nfq_open();
	if (!h) {
		fprintf(stderr, "error during nfq_open()\n");
		exit(1);
	}

	printf("unbinding existing nf_queue handler for AF_INET (if any)\n");
	if (nfq_unbind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_unbind_pf()\n");
		exit(1);
	}

	printf("binding nfnetlink_queue as nf_queue handler for AF_INET\n");
	if (nfq_bind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_bind_pf()\n");
		exit(1);
	}

	printf("binding this socket to queue '0'\n");
	qh = nfq_create_queue(h,  0, &cb, NULL);
	if (!qh) {
		fprintf(stderr, "error during nfq_create_queue()\n");
		exit(1);
	}

	printf("setting copy_packet mode\n");
	if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
		fprintf(stderr, "can't set packet_copy mode\n");
		exit(1);
	}

	fd = nfq_fd(h);

	for (;;) {
		if ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
			printf("pkt received\n");
			nfq_handle_packet(h, buf, rv);
			continue;
		}
		/* if your application is too slow to digest the packets that
		 * are sent from kernel-space, the socket buffer that we use
		 * to enqueue packets may fill up returning ENOBUFS. Depending
		 * on your application, this error may be ignored. nfq_nlmsg_verdict_putPlease, see
		 * the doxygen documentation of this library on how to improve
		 * this situation.
		 */
		if (rv < 0 && errno == ENOBUFS) {
			printf("losing packets!\n");
			continue;
		}
		perror("recv failed");
		break;
	}

	printf("unbinding from queue 0\n");
	nfq_destroy_queue(qh);

#ifdef INSANE
	/* normally, applications SHOULD NOT issue this command, since
	 * it detaches other programs/sockets from AF_INET, too ! */
	printf("unbinding from AF_INET\n");
	nfq_unbind_pf(h, AF_INET);
#endif

	printf("closing library handle\n");
	nfq_close(h);

	exit(0);
}

