from scapy.all import sniff, Raw
from scapy.layers import http


def process_sniffed_packet(packet):
    if packet.haslayer(http.HTTPRequest) and packet.haslayer(Raw):
        print(packet[Raw].load)


def sniffer(interface):
    sniff(iface=interface, store=False, prn=process_sniffed_packet)


if __name__ == '__main__':
    sniffer('eth0')
