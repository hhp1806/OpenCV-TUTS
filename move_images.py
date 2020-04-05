#Chuyển file từ thư mục chứa ảnh vào thư mục images và đánh tên theo thứ tự

import os

folders = [r'C:\Users\hhp18\OneDrive\Desktop\Console_Dataset\Console Dataset__xbox\img', r'C:\Users\hhp18\OneDrive\Desktop\Console_Dataset\Console Dataset__ playstation\img']
path = r'C:\Users\hhp18\OneDrive\Desktop\YOLOv3-Series-master\YOLOv3-Series-master\Labelling\images'


n = 0
for folder in folders:
    for image in os.scandir(folder):
        n+=1
        os.rename(image.path, os.path.join(path, '{:06}.jpg'.format(n)))
