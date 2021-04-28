from PIL import Image
import numpy as np
from numpy import asarray

def main(im1, im2, im3, im4):
    img1 = asarray(Image.open(im1))
    img2 = asarray(Image.open(im2))
    img3 = asarray(Image.open(im3))
    img4 = asarray(Image.open(im4))
    
    FinalImage = np.concatenate((img1, img2, img3, img4), axis = 1)
    x = np.concatenate((img1, img1, img1, img1), axis = 1)
    F = np.concatenate((x, FinalImage), axis = 0)
    data = Image.fromarray(FinalImage)
    data2 = Image.fromarray(F)
    # print(FinalImage.shape)

    data.save("../PlayerAnimate.png")
    data2.save("../PlayerAnimatePro.png")

    


if __name__ == '__main__':
    main("../player1.bmp", "../player2.bmp", "../player3.bmp", "../player4.bmp")