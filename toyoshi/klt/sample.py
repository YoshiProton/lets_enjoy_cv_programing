#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2


WINDOW_NAME = 'camera capture'

drag_start = None
drag_end = None


def mouse_event(event, x, y, flags, param):
    global drag_start
    global drag_end
    
    wname, frame = param
    
    if event == cv2.EVENT_LBUTTONDOWN:
        drag_start = (x, y)

    if event == cv2.EVENT_LBUTTONUP:
        if drag_start:
            drag_start = None
            drag_end = None

    if event == cv2.EVENT_MOUSEMOVE and drag_start:
        drag_end = (x, y)

        
def main():
    cam = cv2.VideoCapture(0)

    cv2.namedWindow(WINDOW_NAME)

    while True:
        ret, frame = cam.read()

        # select rectangle for trakcing
        cv2.setMouseCallback(WINDOW_NAME, mouse_event, [WINDOW_NAME, frame])

        if drag_start and drag_end:
            cv2.rectangle(frame, drag_start, drag_end, (0, 255, 0), 5)

        cv2.imshow(WINDOW_NAME, frame)

        k = cv2.waitKey(1)
        if k == 27:
            break

        # track

        # display tracked rectangle

    cam.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
    
