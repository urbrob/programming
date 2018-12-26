from subprocess import call, check_output
from optparse import OptionParser
import re


def parse_args_for_mac_address():
    parser = OptionParser()
    parser.add_option('-i', '--interface', dest="interface", help='Interface to change Mac Address')
    parser.add_option('-m', '--mac-address', dest='mac_address', help='MAC address change to')
    options = parser.parse_args()[0]
    if not options.interface or not options.mac_address:
        parser.error('[-] Please specify interface and mac_address arguments')
    return [options.interface, options.mac_address]


def test_changed_mac_address(mac_address, interface):
    mac_address_regex = r'\w\w:\w\w:\w\w:\w\w\:\w\w:\w\w'
    ifconfig_result = str(check_output(['ifconfig', interface]))
    mac_address_from_ifconfig = re.search(mac_address_regex, ifconfig_result).group(0)
    return mac_address_from_ifconfig is not None and mac_address_from_ifconfig is mac_address


def change_mac_address(interface, mac_address):
    call(['ifconfig', interface, 'down'])
    call(['ifconfig', interface, 'hw', 'ether', mac_address])
    call(['ifconfig', interface, 'up'])

    if test_changed_mac_address(mac_address, interface):
        print(f'[+] Changed {interface} MAC to {mac_address}')
    else:
        print(f'[-] Couldn\'t change mac address')


if __name__ == '__main__':
    change_mac_address(*parse_args_for_mac_address())
