#! /usr/bin/python3

import requests
from bs4 import BeautifulSoup
import os
import datetime
from time import sleep
import sys
import re

os.system('touch .bing.txt')
os.system('mkdir -p Bing')

while True:
    fr = open('.bing.txt','r')
    bing = fr.read() 
    fr.close()
    fw = open('.bing.txt','a')
    while True:
        try:
            url = 'http://bingwallpaper.com/'
            sc = requests.get(url)
            soup = BeautifulSoup(sc.text,'lxml')
            image_text = soup.select('.panel-overlay p')
            break
        except requests.exceptions.ConnectionError:
            continue
    if image_text[0].text[1:9] not in bing:
        while True:
            try:
                image = soup.select('.cursor_zoom img')
                image_url = image[0].get('src')
                res = requests.get(image_url)
                with open(os.path.join('Bing',image_text[0].text[1:9]+'.jpg'),'wb') as file:
                    file.write(res.content) 
		string = os.getcwd()
                os.system('gsettings set org.gnome.desktop.background picture-uri file:///'+string+'/Bing/'+image_text[0].text[1:9]+'.jpg')
           	
		fw.write(image_text[0].text[1:9]+'\n')
              	fw.close()
                break
            except requests.exceptions.ConnectionError:
                continue
    print ('Going to sleep')
    sleep (1800)
