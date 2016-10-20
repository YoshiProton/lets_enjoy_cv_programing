# -*- coding: utf-8 -*-

import util
import cv2
import numpy as np
import const

IMG_DIR = "../img/"

if __name__ == '__main__':
    try:
        img_path = IMG_DIR + "tegaki.jpg"
        # 画像読み込み
        img = util.ImageProcessing.loadImg(img_path)
        # グレースケール画像に変換
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # 2値化処理
        ret, th_img = cv2.threshold(gray_img, 128, 255, cv2.THRESH_BINARY)
        # 細線化処理 9-3-2
        thin_img = util.ImageProcessing.thinning(th_img)
        # セグメント処理 9-3-3
        seg_img = util.ImageProcessing.segment(thin_img)
        thin_color_img = cv2.cvtColor(thin_img, cv2.COLOR_GRAY2BGR)
        thin_color_img = seg_img if seg_img != [0,0,0] else thin_color_img
        # ベクトル化 9-3-4

        # print [255 if v == 2 else 0 for inner_list in koritsu_img for v in inner_list]

        cv2.imshow("org", img)
        cv2.imshow("gray", gray_img)
        cv2.imshow("th", th_img)
        cv2.imshow("thin", thin_img)
        cv2.imshow("seg", thin_color_img)
        cv2.waitKey()
    except Exception as e:
        print str(e)
