from scapy.all import ARP, Ether, srp
from argparse import ArgumentParser


class NetworkScanner():
    def scan(self, ip):
        arp_request = ARP(pdst=ip)
        broadcast = Ether(dst='ff:ff:ff:ff:ff:ff')
        arp_request_broadcast = broadcast / arp_request
        answers = srp(arp_request_broadcast, timeout=1, verbose=False)[0]
        return answers

    def get_mac_from_ip(self, ip):
        return self.scan(ip)[0][1].hwsrc

    def print_result(self, answers):
        print("\tIP\t\t\tAt MAC Address\n------------------------------------")
        for index, element in enumerate(answers):
            print(f'{index} - {element[1].psrc} \t\t {element[1].hwsrc} \n')

    def get_wlan_ip_from_ip(self, ip):
        ip = ip.split('.')
        ip[3] = '1/24'
        ip = '.'.join(ip)
        return ip


def target_ip_parser():
    parser = ArgumentParser()
    parser.add_argument('-t', '--target', dest="target", help='Target IP for ARP request')
    options = parser.parse_args()
    if not options.target:
        parser.error('[-] Please specify your target address')
    return options.target


if __name__ == '__main__':
    target_ip = target_ip_parser()
    answers = NetworkScanner().scan(target_ip)
    _print_result(answers)
