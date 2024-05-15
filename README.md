# 가상머신 기준입니다.

## set에 해당 주소가 존재할 때 걸리는 시간

entering callback
pkt received
hw_protocol=0x0800 hook=3 id=78 outdev=2 payload_len=165
IP src = 192.168.247.131
IP dst = 172.217.161.238
TCP src = 41680
TCP dst = 80
total = 165, ip = 20, tcp = 20 
http_len = 125
HTTP
47 45 54 20 2F 20 48 54 54 50 2F 31 2E 31 0D 0A 
48 6F 73 74 3A 20 67 6F 6F 67 6C 65 2E 63 6F 6D 
0D 0A 55 73 65 72 2D 41 67 65 6E 74 3A 20 57 67 
65 74 2F 31 2E 32 31 2E 32 0D 0A 41 63 63 65 70 
74 3A 20 2A 2F 2A 0D 0A 41 63 63 65 70 74 2D 45 
6E 63 6F 64 69 6E 67 3A 20 69 64 65 6E 74 69 74 
79 0D 0A 43 6F 6E 6E 65 63 74 69 6F 6E 3A 20 4B 
65 65 70 2D 41 6C 69 76 65 0D 0A 0D 0A 
GET / HTTP/1.1
Host: google.com
User-Agent: Wget/1.21.2
Accept: */*
Accept-Encoding: identity
Connection: Keep-Alive


google.com
7.136e-06 seconds.
google.comis not allowed.


## set에 해당 주소가 존재하지 않을 때 걸리는 시간

entering callback
pkt received
hw_protocol=0x0800 hook=3 id=132 outdev=2 payload_len=487
IP src = 192.168.247.131
IP dst = 180.67.148.140
TCP src = 54780
TCP dst = 80
total = 487, ip = 20, tcp = 20 
http_len = 447
HTTP
47 45 54 20 2F 20 48 54 54 50 2F 31 2E 31 0D 0A 
48 6F 73 74 3A 20 67 69 6C 67 69 6C 2E 6E 65 74 
0D 0A 55 73 65 72 2D 41 67 65 6E 74 3A 20 4D 6F 
7A 69 6C 6C 61 2F 35 2E 30 20 28 58 31 31 3B 20 
55 62 75 6E 74 75 3B 20 4C 69 6E 75 78 20 78 38 
36 5F 36 34 3B 20 72 76 3A 31 32 36 2E 30 29 20 
47 65 63 6B 6F 2F 32 30 31 30 30 31 30 31 20 46 
69 72 65 66 6F 78 2F 31 32 36 2E 30 0D 0A 41 63 
63 65 70 74 3A 20 74 65 78 74 2F 68 74 6D 6C 2C 
61 70 70 6C 69 63 61 74 69 6F 6E 2F 78 68 74 6D 
6C 2B 78 6D 6C 2C 61 70 70 6C 69 63 61 74 69 6F 
6E 2F 78 6D 6C 3B 71 3D 30 2E 39 2C 69 6D 61 67 
65 2F 61 76 69 66 2C 69 6D 61 67 65 2F 77 65 62 
70 2C 2A 2F 2A 3B 71 3D 30 2E 38 0D 0A 41 63 63 
65 70 74 2D 4C 61 6E 67 75 61 67 65 3A 20 65 6E 
2D 55 53 2C 65 6E 3B 71 3D 30 2E 35 0D 0A 41 63 
63 65 70 74 2D 45 6E 63 6F 64 69 6E 67 3A 20 67 
7A 69 70 2C 20 64 65 66 6C 61 74 65 0D 0A 43 6F 
6E 6E 65 63 74 69 6F 6E 3A 20 6B 65 65 70 2D 61 
6C 69 76 65 0D 0A 43 6F 6F 6B 69 65 3A 20 50 48 
50 53 45 53 53 49 44 3D 62 31 64 39 36 37 62 63 
35 35 66 61 35 34 61 31 34 65 32 39 35 30 30 62 
32 63 30 35 31 30 39 61 3B 20 73 73 6F 3D 62 32 
33 37 36 63 61 64 64 63 61 37 37 65 64 65 64 62 
66 39 36 30 38 35 34 64 35 38 32 36 62 33 0D 0A 
55 70 67 72 61 64 65 2D 49 6E 73 65 63 75 72 65 
2D 52 65 71 75 65 73 74 73 3A 20 31 0D 0A 50 72 
69 6F 72 69 74 79 3A 20 75 3D 31 0D 0A 0D 0A 
GET / HTTP/1.1
Host: gilgil.net
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:126.0) Gecko/20100101 Firefox/126.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Cookie: PHPSESSID=b1d967bc55fa54a14e29500b2c05109a; sso=b2376caddca77ededbf960854d5826b3
Upgrade-Insecure-Requests: 1
Priority: u=1


gilgil.net
OK
9.229e-06 seconds.

## file을 읽어 올 때 걸린 시간
jsw5203@jsw5203-virtual-machine:~/ip$ sudo ./1m-block top-1m.txt
1.81241 seconds.
## top 결과 메모리 16기가중 0.4% 점유
top - 18:02:38 up  2:38,  2 users,  load average: 0.34, 0.59, 0.75
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
%Cpu(s):  7.2 us,  2.4 sy,  0.0 ni, 89.8 id,  0.0 wa,  0.0 hi,  0.6 si,  0.0 st
MiB Mem :  15948.6 total,   6031.7 free,   2647.0 used,   7269.9 buff/cache
MiB Swap:   2048.0 total,   2048.0 free,      0.0 used.  12806.1 avail Mem 

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                          
  34979 root      20   0   75084  72836   3712 S   0.0   0.4   0:01.71 1m-block


