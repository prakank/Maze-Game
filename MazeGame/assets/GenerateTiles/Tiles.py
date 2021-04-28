import numpy as np
# import image as im
from PIL import Image as im

TileWidth = 32
TileHeight = 32
RowsTocolor = 3;

L = np.zeros((TileWidth, TileHeight))

flag = [ [0,0,0,0], [0,0,0,1], [0,0,1,0], [0,1,0,0], [1,0,0,0], [0,0,1,1], [0,1,0,1], [1,0,0,1], [0,1,1,0], [1,0,1,0], [1,1,0,0], [0,1,1,1], [1,0,1,1], [1,1,0,1], [1,1,1,0], [1,1,1,1]]

# 1 means pixel values will be black

# Black Background
#      333
#     0   2
#     0   2
#     0   2
#      111

def main(color, TileBackground, Linecolor):
    cnt=0
    for i in flag:
        temp = np.zeros((TileWidth, TileHeight))

        for p in range(temp.shape[0]):
            for q in range(temp.shape[1]):
                temp[p][q] = TileBackground
        
        if(i[3] == 1):
            for j in range(RowsTocolor):
                for k in range(len(temp[j])):
                    temp[j][k] = Linecolor;
        if(i[2] == 1):
            for j in range(RowsTocolor):
                for k in range(len(temp[j])):
                    temp[k][len(temp[j]) - j - 1] = Linecolor;
        if(i[1] == 1):
            for j in range(RowsTocolor):
                for k in range(len(temp[j])):
                    temp[len(temp[j]) - j - 1][k] = Linecolor;
        if(i[0] == 1):
            for j in range(RowsTocolor):
                for k in range(len(temp[j])):
                    temp[k][j] = Linecolor;

        temp = np.array(temp, np.uint8)
        data = im.fromarray(temp)
        
        data.save(color + "_" + str(cnt) + ".png")
        cnt = cnt+1
        

if __name__ == '__main__':
    main("Black", 0, 255)
    main("White", 255, 0)
