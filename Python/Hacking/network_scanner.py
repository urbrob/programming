from scapy.all import ARP, Ether, srp
from argparse import ArgumentParser



def scan(ip):
    arp_request = ARP(pdst=ip)
    broadcast = Ether(dst='ff:ff:ff:ff:ff:ff')
    arp_request_broadcast = broadcast / arp_request
    answers = srp(arp_request_broadcast, timeout=1, verbose=False)[0]
    return answers


def get_mac_from_ip(ip):
    return scan(ip)[0][1].hwsrc


def _target_ip_parser():
    parser = ArgumentParser()
    parser.add_argument('-t', '--target', dest="target", help='Target IP for ARP request')
    options = parser.parse_args()
    if not options.target:
        parser.error('[-] Please specify your target address')
    return options.target


def _print_result(answers):
    print("IP\t\t\tAt MAC Address\n------------------------------------")
    for element in answers:
        print(f'{element[1].psrc} \t\t {element[1].hwsrc} \n')



if __name__ == '__main__':
    target_ip = _target_ip_parser()
    answers = scan(target_ip)
    _print_result(answers)
