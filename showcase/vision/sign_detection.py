from ultralytics import YOLO
from PIL import Image
import cv2
import serial # Seri iletişim için
#from dikdortgen import Tespit

model = YOLO('merdiven200.pt')
#results = model.predict(source=0, show = True)
import time
import socket


import numpy as np
#from toplanma import Tabela



#s Soket oluşturma
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('127.0.0.1', 5555))
server_socket.listen(1)

print("Python sunucusu başlatıldı. Bekleniyor...")

# Bağlantıyı kabul etme
client_socket, addr = server_socket.accept()
#ser = serial.Serial('com4', 9600,timeout=1)

blue2=0
red2=0
yellow2=0
green2=0
def tabela():
    global blue2
    global red2
    global yellow2
    global green2
    y=0
    cap = cv2.VideoCapture("http://192.168.0.107:8080/?action=stream")
    #cap = cv2.VideoCapture(0)
    client_socket.settimeout(0.01)  # Soket için zaman aşımı belirle
    while(cap.isOpened()):
        
      ret,img = cap.read()
      img = cv2.resize(img, (800, 600))
      results = model(img, stream=True)
    
      #Controlling the algorithm with keys
      try:
          for r in results:
         
              boxes = r.boxes
              for box in boxes:
                  
                  x1, y1, x2, y2 = box.xyxy[0]
                  x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
    
    
                  # Class Name
                  cls = int(box.cls[0])
                  conf = int(box.conf[0]*100)
                  print(conf)
                  print(cls)
                  
    
                  # 0 insan 2 araba
                  if (cls == 0 or cls == 1 or cls == 2) and conf>75: # insan algılandığında
                      if   cls==2: 
                          cv2.rectangle(img, (x1, y1), (x2, y2), (255, 0, 255), 3)
                          cv2.putText(img, "Toplanma Alani %", (x1, y1+30), cv2.FONT_HERSHEY_SIMPLEX,.8,(0, 0, 255), 3)
                          cv2.putText(img, str(conf), (x1+250, y1+30), cv2.FONT_HERSHEY_SIMPLEX,.8,(0, 0, 255), 3)
                      elif   cls==1: 
                         cv2.rectangle(img, (x1, y1), (x2, y2), (255, 0, 255), 3)
                         cv2.putText(img, "Merdiven inisi %" ,(x1, y1+30), cv2.FONT_HERSHEY_SIMPLEX,.8,(0, 0, 255), 3)
                         cv2.putText(img, str(conf), (x1+250, y1+30), cv2.FONT_HERSHEY_SIMPLEX,.8,(0, 0, 255), 3)
                      elif   cls==0: 
                         cv2.rectangle(img, (x1, y1), (x2, y2), (255, 0, 255), 3)
                         cv2.putText(img, "Dogalgaz Vanasi %",(x1, y1+30), cv2.FONT_HERSHEY_SIMPLEX,.8,(0, 0, 255), 3)
                         cv2.putText(img, str(conf), (x1+250, y1+30), cv2.FONT_HERSHEY_SIMPLEX,.8,(0, 0, 255), 3)
                   
                      
          cv2.imshow('Otonom Aydinlatma',img)
                     
          a = cv2.waitKey(1)
          try:
              data = client_socket.recv(1024)
              if data:
                  veri = data.decode()
                  print(veri)
                  if veri =="s":
                      yellow2+=1
                  elif veri =="k":
                      red2=red2+1   
                  elif veri =="m":
                      blue2=blue2+1
                  elif veri =="y":
                      green2=green2+1
                      
                  elif veri =="3":
                      break
          except socket.timeout:
              pass
      
              
          
          
      except cv2.error:
          print("stream ended")
          break
    
    cap.release()
    # Bağlantıyı kapatma
    #client_socket.close()
    #server_socket.close()
    
    try:
        # Soketten gelen veriyi al
        client_socket.settimeout(3)
        data = client_socket.recv(1024)
        while True:
            chunk = client_socket.recv(1024)
            if not chunk:
                break
            data += chunk
       
    except (socket.timeout, ConnectionResetError):
        # Timeout veya bağlantı hatası oluşursa işlemi sonlandır
        pass
    tespit()
    #Tespit.tespit(client_socket)

def tespit():
    cap = cv2.VideoCapture("http://192.168.0.107:8080/?action=stream")
    #cap = cv2.VideoCapture(0)
    blue1=0
    red1=0
    yellow1=0
    green1=0
    fourcc = cv2.VideoWriter_fourcc(*'MJPG')
    cap.set(6, fourcc)
    cap.set(5, 24)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
    #brightness
    cap.set(10, 10)
    #cotrast
    cap.set(11, 0)
    #saturation
    cap.set(12, 100)
    #hue
    cap.set(13, 0)
    #gain
    cap.set(14, 5)
    #exposure
    cap.set(15, 156)
    #white-balance
    cap.set(17, 4600)
    
    # img=cv2.imread("asd.jpg")
    # gri=cv2.cvtColor((img), cv2.COLOR_BGR2GRAY)
    # gri=np.float32(gri)
    # hsv=cv2.cvtColor((img), cv2.COLOR_BGR2HSV)
    # hsv=np.float32(hsv)
    # corner=cv2.goodFeaturesToTrack(gri, 40,0.01,10)
    # corner=np.int0(corner)
    a=0
    b=0

    client_socket.settimeout(0.01)  # Soket için zaman aşımı belirle
    while (True):
      try:
          data = client_socket.recv(1024)
          if data:
              veri = data.decode()
              
              print(veri)
              if veri=="3":
                  break;
              elif veri=="w":
                  b=1
      except socket.timeout:
          pass
      
      blue=0
      red=0
      yellow=0
      green=0
      ret, videoGoruntu = cap.read()
    
      hsv = cv2.cvtColor(videoGoruntu, cv2.COLOR_BGR2HSV)
      lower_blue = np.array([70, 50, 50])
      upper_blue = np.array([135, 250, 250])
      
      lower_red = np.array([150, 30, 30])
      upper_red = np.array([200, 250, 250])
      
      lower_green = np.array([30, 30, 30])
      upper_green = np.array([90, 250, 250])
      
      lower_yellow = np.array([20, 30, 30])
      upper_yellow = np.array([50, 250, 250])
      
      mask_blue = cv2.inRange(hsv, lower_blue, upper_blue)
      result_blue = cv2.bitwise_and(hsv, hsv, mask=mask_blue)
      result_blue = cv2.cvtColor(result_blue, cv2.COLOR_HSV2BGR)
      
      mask_red = cv2.inRange(hsv, lower_red, upper_red)
      result_red = cv2.bitwise_and(hsv, hsv, mask=mask_red)
      result_red = cv2.cvtColor(result_red, cv2.COLOR_HSV2BGR)
      
      mask_green = cv2.inRange(hsv, lower_green, upper_green)
      result_green = cv2.bitwise_and(hsv, hsv, mask=mask_green)
      result_green = cv2.cvtColor(result_green, cv2.COLOR_HSV2BGR)
      
      mask_yellow = cv2.inRange(hsv, lower_yellow, upper_yellow)
      result_yellow = cv2.bitwise_and(hsv, hsv, mask=mask_yellow)
      result_yellow = cv2.cvtColor(result_yellow, cv2.COLOR_HSV2BGR)
    
     
      
      #mx, my = getContours(blurred, img)
      contours_blue, _ = cv2.findContours(mask_blue, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)  
      contours_red, _ = cv2.findContours(mask_red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
      contours_green, _ = cv2.findContours(mask_green, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
      contours_yellow, _ = cv2.findContours(mask_yellow, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
      mx = 0
      my = 0
     
      for cnt in contours_blue:
      
            peri = cv2.arcLength(cnt, False)
            approx = cv2.approxPolyDP(cnt, 0.02*peri, False)
            objCor = len(approx)
            x, y, w, h = cv2.boundingRect(approx)
            area = w*h
            if area > 50000:
                print(w," ",h, " ",area)
                blue=blue+1
                if blue>0:
                    blue1=blue
                cv2.drawContours(videoGoruntu, cnt, -1, (255,0,0), 3)
                cv2.rectangle(videoGoruntu, (x,y), (x+w, y+h), (255,0,0), 2)
                cv2.circle(videoGoruntu, (mx,my), 3, (0,0,255), 3)
                mx = int(x+(w/2))
                my = int(y+(h/2))
      for cnt in contours_red:
      
          peri = cv2.arcLength(cnt, False)
          approx = cv2.approxPolyDP(cnt, 0.02*peri, False)
          objCor = len(approx)
          x, y, w, h = cv2.boundingRect(approx)
          area = w*h
          if area > 50000:
              red=red+1
              if red>0:
                  red1=red
              cv2.drawContours(videoGoruntu, cnt, -1, (0,0,255), 3)
              cv2.rectangle(videoGoruntu, (x,y), (x+w, y+h), (0,0,255), 2)
              cv2.circle(videoGoruntu, (mx,my), 3, (0,0,255), 3)
              mx = int(x+(w/2))
              my = int(y+(h/2))
      for cnt in contours_yellow:
      
          peri = cv2.arcLength(cnt, False)
          approx = cv2.approxPolyDP(cnt, 0.02*peri, False)
          objCor = len(approx)
          x, y, w, h = cv2.boundingRect(approx)
          area = w*h
          if area > 50000:
              yellow=yellow+1
              if yellow>0:
                  yellow1=yellow
              cv2.drawContours(videoGoruntu, cnt, -1, (0,255,255), 3)
              cv2.rectangle(videoGoruntu, (x,y), (x+w, y+h), (0,255,255), 2)
              cv2.circle(videoGoruntu, (mx,my), 3, (0,0,255), 3)
              mx = int(x+(w/2))
              my = int(y+(h/2))
      for cnt in contours_green:
      
          peri = cv2.arcLength(cnt, False)
          approx = cv2.approxPolyDP(cnt, 0.02*peri, False)
          objCor = len(approx)
          x, y, w, h = cv2.boundingRect(approx)
          area = w*h
          if area > 50000:
              green=green+1
              if green>0:
                  green1=green
              cv2.drawContours(videoGoruntu, cnt, -1, (0,255,0), 3)
              cv2.rectangle(videoGoruntu, (x,y), (x+w, y+h), (0,255,0), 2)
              cv2.circle(videoGoruntu, (mx,my), 3, (0,0,255), 3)
              mx = int(x+(w/2))
              my = int(y+(h/2))
      if b==1:
          
          yazi=str(blue2)+" mavi "+str(red2)+" kirmizi "+str(yellow2)+" sari "+str(green2)+" yesil kutu var"
      else:
          yazi=str(blue1)+" mavi "+str(red1)+" kirmizi "+str(yellow1)+" sari "+str(green1)+" yesil kutu var"
      cv2.putText(videoGoruntu, yazi, (20, 20), cv2.FONT_HERSHEY_SIMPLEX,.8,(0, 0, 255), 3)
      cv2.imshow("Bilgisayar Kamerasi", videoGoruntu)
      # cv2.imshow("result_blue", result_blue)
      # cv2.imshow("result_red", result_red)
      # cv2.imshow("result_yellow", result_yellow)
      # cv2.imshow("result_green", result_green)
      
      
      if b==1:
          print("mavi= ",blue2," kırmızı= ",red2," sarı= ",yellow2," yeşil= ",green2)
      else:
      
          print("mavi= ",blue1," kırmızı= ",red1," sarı= ",yellow1," yeşil= ",green1)
      if cv2.waitKey(50) & 0xFF == ord('x'):
          break
    
    cap.release()
    cv2.destroyAllWindows()
    
    # try:
    #     # Soketten gelen veriyi al
    #     client_socket.settimeout(3)
    #     data = client_socket.recv(1024)
    #     while True:
    #         chunk = client_socket.recv(1024)
    #         print(chunk)
    #         if not chunk:
    #             break
    #         data += chunk
       
    # except (socket.timeout, ConnectionResetError):
    #     # Timeout veya bağlantı hatası oluşursa işlemi sonlandır
    #     pass
    tabela()
    #Tabela.tabela()
tabela()



